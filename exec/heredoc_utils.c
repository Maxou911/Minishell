/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:15:42 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/06/29 23:01:04 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_input_redirection(t_exec *exec, t_redir_type *redir)
{
	exec->infile = open(redir->file, O_RDONLY);
	if (exec->infile == -1)
	{
		perror(redir->file);
		return (1);
	}
	return (0);
}

static int	handle_output_redirection(t_exec *exec, t_redir_type *redir)
{
	exec->outfile = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (exec->outfile == -1)
	{
		close(exec->outfile);
		exec->last_exit_status = 1;
		return (perror(redir->file), 1);
	}
	return (0);
}

static int	handle_append_redirection(t_exec *exec, t_redir_type *redir)
{
	exec->outfile = open(redir->file, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (exec->outfile == -1)
	{
		exec->last_exit_status = 1;
		return (perror(redir->file), 1);
	}
	return (0);
}

static int	handle_single_redirection(t_redir_type *redir, t_exec *exec)
{
	if (redir->type == INPUT)
		return (handle_input_redirection(exec, redir));
	else if (redir->type == OUTPUT)
		return (handle_output_redirection(exec, redir));
	else if (redir->type == HEREDOC)
		return (handle_heredoc(exec, redir));
	else if (redir->type == APPEND)
		return (handle_append_redirection(exec, redir));
	return (0);
}

int	handle_redirections(t_redir_type *redir, t_exec *exec)
{
	while (redir)
	{
		if (handle_single_redirection(redir, exec) != 0)
			return (1);
		redir = redir->next;
	}
	return (0);
}
