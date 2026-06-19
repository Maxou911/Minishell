/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:17:28 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/07/28 23:56:34 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/exec.h"

void	token_to_word(t_token *token, t_cmd *current)
{
	char	**new_args;
	int		size;
	int		i;

	size = count_args(current->args);
	new_args = malloc(sizeof(char *) * (size + 2));
	if (!new_args)
		return ;
	i = 0;
	while (i < size)
	{
		new_args[i] = current->args[i];
		i++;
	}
	new_args[i++] = ft_strdup(token->value);
	new_args[i] = NULL;
	free(current->args);
	current->args = new_args;
}

void	token_to_operator(t_token *token, t_cmd *current)
{
	t_redir_type	*new_redir;
	t_redir_type	*tmp;

	new_redir = malloc(sizeof(t_redir_type));
	if (!new_redir)
		return ;
	new_redir->file = ft_strdup(token->next->value);
	new_redir->type = token->type;
	new_redir->next = NULL;
	if (!current->redirs)
		current->redirs = new_redir;
	else
	{
		tmp = current->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
}

void	token_to_cmd(t_token *tokens, t_cmd *current)
{
	while (tokens)
	{
		if (tokens->type == WORD)
		{
			token_to_word(tokens, current);
		}
		else if (tokens->type == INPUT || tokens->type == OUTPUT
			|| tokens->type == APPEND || tokens->type == HEREDOC)
		{
			if (!tokens->next)
				break ;
			token_to_operator(tokens, current);
			tokens = tokens->next;
		}
		else if (tokens->type == PIPE)
		{
			current->next = ft_calloc(1, sizeof(t_cmd));
			current = current->next;
		}
		tokens = tokens->next;
	}
}

static int	validate_single_token(t_token *token, t_exec *exec)
{
	if (token->type == PIPE
		&& (!token->next || token->next->type != WORD))
	{
		printf("Syntax error near unexpected token '%s'\n", token->value);
		exec->last_exit_status = 2;
		return (0);
	}
	if ((token->type == INPUT || token->type == OUTPUT || \
			token->type == APPEND || token->type == HEREDOC)
		&& (!token->next || token->next->type != WORD))
	{
		printf("Syntax error near unexpected token '%s'\n", token->value);
		exec->last_exit_status = 2;
		return (0);
	}
	return (1);
}

int	validate_tokens(t_token *tokens, t_exec *exec)
{
	if (tokens && tokens->type == PIPE)
	{
		printf("Syntax error near unexpected token '%s'\n", tokens->value);
		exec->last_exit_status = 2;
		return (0);
	}
	while (tokens)
	{
		if (!validate_single_token(tokens, exec))
			return (0);
		tokens = tokens->next;
	}
	return (1);
}
