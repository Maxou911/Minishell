/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:22:34 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/06/28 00:38:26 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/exec.h"

static void	process_operator_token(char **line_ptr, t_token **tokens)
{
	char	*value;

	value = extract_operator(line_ptr);
	add_token(tokens, value, get_token_type(value));
	free(value);
}

static int	process_word_token(char **line_ptr, t_token **tokens)
{
	char	*value;

	value = extract_word(line_ptr);
	if (!value)
		return (0);
	add_token(tokens, value, get_token_type(value));
	free(value);
	return (1);
}

static int	process_single_token(char **line_ptr, t_token **tokens)
{
	if (is_operator(line_ptr))
	{
		process_operator_token(line_ptr, tokens);
		return (1);
	}
	else if (is_word(line_ptr))
		return (process_word_token(line_ptr, tokens));
	else
	{
		(*line_ptr)++;
		return (1);
	}
}

void	identify_token(char **line, t_token **tokens)
{
	char	*line_copy;
	char	*line_ptr;
	int		error;

	line_copy = ft_strdup(*line);
	if (!line_copy)
		return ;
	line_ptr = line_copy;
	error = 0;
	while (*line_ptr && !error)
	{
		skip_space(&line_ptr);
		if (!*line_ptr)
			break ;
		if (!process_single_token(&line_ptr, tokens))
			error = 1;
	}
	if (error)
	{
		free_tokens(*tokens);
		*tokens = NULL;
	}
	free(line_copy);
}
