/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:41:07 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/06/29 20:27:05 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	setup_child_redirections(t_exec *exec)
{
	if (exec->infile != STDIN_FILENO)
	{
		dup2(exec->infile, STDIN_FILENO);
		close(exec->infile);
	}
}

static void	read_and_write_loop(void)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		if (write(STDOUT_FILENO, buffer, bytes_read) == -1)
		{
			perror("write");
			exit(1);
		}
		bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
	}
	if (bytes_read == -1)
	{
		perror("read");
		exit(1);
	}
}

static void	handle_child_process(t_cmd *cmds, t_exec *exec)
{
	if (handle_redirections(cmds->redirs, exec) != 0)
		exit(exec->last_exit_status);
	setup_child_redirections(exec);
	reset_signals_child();
	read_and_write_loop();
	exit(0);
}

static void	handle_parent_process(pid_t pid, t_exec *exec)
{
	int	status;

	ignore_sigint();
	waitpid(pid, &status, 0);
	setup_signal_main_shell();
	if (WIFEXITED(status))
		exec->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			exec->last_exit_status = 130;
			write(1, "\n", 1);
		}
		else
			exec->last_exit_status = 128 + WTERMSIG(status);
	}
}

void	handle_redirections_only(t_cmd *cmds, t_exec *exec)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		reset_signals_child();
		handle_child_process(cmds, exec);
	}
	else
	{
		set_signals_heredoc_parent();
		handle_parent_process(pid, exec);
		setup_signal_main_shell();
	}
}
