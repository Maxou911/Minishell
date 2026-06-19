/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:30:37 by maalwis           #+#    #+#             */
/*   Updated: 2025/06/21 15:32:19 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_heredoc(t_exec *exec, t_redir_type *redir)
{
	int		heredoc_pipe[2];
	pid_t	pid;

	if (setup_heredoc_pipe(heredoc_pipe) != 0)
		return (1);
	pid = fork();
	if (pid == -1)
		return (perror("fork heredoc"), 1);
	if (pid == 0)
		return (handle_heredoc_child_process(redir, heredoc_pipe));
	else
		return (handle_heredoc_parent_process(exec, heredoc_pipe, pid));
}
