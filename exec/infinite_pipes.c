/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:32:33 by maalwis           #+#    #+#             */
/*   Updated: 2025/07/28 21:13:01 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	init_pipes_execution(t_exec *exec)
{
	exec->exit_status = 0;
	exec->pid = malloc(sizeof(pid_t) * exec->nb_cmds);
	if (!exec->pid)
		return (perror("malloc pid"), exit(1), 1);
	exec->prev_fd = -1;
	exec->index = 0;
	return (0);
}

static int	execute_single_pipe(t_cmd *cmd, t_exec *exec, char **envp)
{
	exec->pipe_fd[0] = -1;
	exec->pipe_fd[1] = -1;
	if (exec->index < exec->nb_cmds - 1 && pipe(exec->pipe_fd) == -1)
		return (perror("pipe"), exit(1), 1);
	exec->pid[exec->index] = fork();
	if (exec->pid[exec->index] == -1)
		return (perror("fork"), exit(1), 1);
	if (exec->pid[exec->index] == 0)
		child_process(cmd, exec, envp);
	else
		parent_process(exec);
	return (0);
}

static int	execute_pipe_loop(t_cmd *cmd, t_exec *exec, char **envp)
{
	while (exec->index < exec->nb_cmds)
	{
		if (execute_single_pipe(cmd, exec, envp) != 0)
			return (1);
		exec->index++;
		cmd = cmd->next;
	}
	return (0);
}

static int	wait_for_children(t_exec *exec)
{
	int	sig;

	exec->i = 0;
	while (exec->i < exec->nb_cmds)
		waitpid(exec->pid[exec->i++], &exec->exit_status, 0);
	setup_signal_main_shell();
	if (WIFSIGNALED(exec->exit_status))
	{
		sig = WTERMSIG(exec->exit_status);
		if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 20);
		else if (sig == SIGINT)
			write(1, "\n", 1);
		exec->last_exit_status = 128 + sig;
	}
	if (WIFEXITED(exec->exit_status))
		exec->last_exit_status = WEXITSTATUS(exec->exit_status);
	return (0);
}

void	infinite_pipes(t_cmd *cmd, t_exec *exec, char **envp)
{
	if (init_pipes_execution(exec) != 0)
		return ;
	expand_all_args(cmd, exec->last_exit_status);
	ignore_sigint();
	if (execute_pipe_loop(cmd, exec, envp) != 0)
		return ;
	wait_for_children(exec);
	setup_signal_main_shell();
	if (exec->prev_fd != -1)
		close(exec->prev_fd);
	free(exec->pid);
	close_fd(exec);
}
