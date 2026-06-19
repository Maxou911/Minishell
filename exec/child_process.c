/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:28:49 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/06/29 22:40:18 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_redirections(t_cmd *cmd, t_exec *exec, int *local_in,
int *local_out)
{
	*local_in = STDIN_FILENO;
	*local_out = STDOUT_FILENO;
	if (cmd->redirs)
	{
		if (handle_redirections(cmd->redirs, exec) != 0)
			exit(exec->last_exit_status);
		if (exec->infile != STDIN_FILENO)
			*local_in = exec->infile;
		if (exec->outfile != STDOUT_FILENO)
			*local_out = exec->outfile;
	}
}

void	apply_redirections(t_exec *exec, int local_in, int local_out)
{
	if (exec->index == 0)
	{
		if (local_in != STDIN_FILENO)
			safe_dup2(local_in, STDIN_FILENO);
	}
	else
	{
		if (local_in != STDIN_FILENO)
			safe_dup2(local_in, STDIN_FILENO);
		else
			safe_dup2(exec->prev_fd, STDIN_FILENO);
	}
	if (exec->index == exec->nb_cmds - 1)
	{
		if (local_out != STDOUT_FILENO)
			safe_dup2(local_out, STDOUT_FILENO);
	}
	else
	{
		if (local_out != STDOUT_FILENO)
			safe_dup2(local_out, STDOUT_FILENO);
		else
			safe_dup2(exec->pipe_fd[1], STDOUT_FILENO);
	}
}

void	child_process(t_cmd *cmd, t_exec *exec, char **envp)
{
	int	local_in;
	int	local_out;

	setup_redirections(cmd, exec, &local_in, &local_out);
	apply_redirections(exec, local_in, local_out);
	if (local_in != STDIN_FILENO)
		close(local_in);
	if (local_out != STDOUT_FILENO)
		close(local_out);
	close_fd(exec);
	reset_signals_child();
	execute_command(cmd, envp);
}
