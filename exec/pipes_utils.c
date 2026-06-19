/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:37:08 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/06/29 22:40:05 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	safe_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		exit (1);
	}
}

void	close_fd(t_exec *exec)
{
	if (exec->prev_fd != -1)
		close(exec->prev_fd);
	if (exec->pipe_fd[0] != -1)
		close(exec->pipe_fd[0]);
	if (exec->pipe_fd[1] != -1)
		close(exec->pipe_fd[1]);
}

void	parent_process(t_exec *exec)
{
	if (exec->prev_fd != -1)
		close(exec->prev_fd);
	if (exec->pipe_fd[1] != -1)
		close(exec->pipe_fd[1]);
	exec->prev_fd = exec->pipe_fd[0];
}

int	count_cmds(t_cmd *cmd, t_exec *exec)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		exec->nb_cmds++;
		temp = temp->next;
	}
	return (exec->nb_cmds);
}
