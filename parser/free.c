/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:13:54 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/06/21 16:16:16 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/exec.h"

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
}

static void	free_cmd_args(t_cmd *cmd)
{
	int	i;

	if (!cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
		free(cmd->args[i++]);
	free(cmd->args);
}

static void	free_cmd_redirections(t_cmd *cmd)
{
	t_redir_type	*redir;
	t_redir_type	*tmp_redir;

	if (!cmd->redirs)
		return ;
	redir = cmd->redirs;
	while (redir)
	{
		tmp_redir = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp_redir;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp_cmd;

	while (cmd)
	{
		tmp_cmd = cmd->next;
		free_cmd_args(cmd);
		free_cmd_redirections(cmd);
		free(cmd);
		cmd = tmp_cmd;
	}
}
