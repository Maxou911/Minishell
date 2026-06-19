/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:05:10 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/06/26 17:33:08 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/exec.h"

t_token_type	get_token_type(char *line)
{
	if (ft_strncmp(line, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(line, ">>", 2) == 0)
		return (APPEND);
	if (line[0] == '<')
		return (INPUT);
	if (line[0] == '>')
		return (OUTPUT);
	if (line[0] == '|')
		return (PIPE);
	return (WORD);
}

void	skip_space(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
}

void	skip_quotes(char **line)
{
	char	quote;

	if (!line || !*line || !(**line == '\'' || **line == '\"'))
		return ;
	quote = **line;
	(*line)++;
	while (**line && **line != quote)
		(*line)++;
	if (**line == quote)
		(*line)++;
}

int	is_operator(char **line)
{
	if ((*line)[0] == '>' && (*line)[1] == '>')
		return (1);
	if ((*line)[0] == '<' && (*line)[1] == '<')
		return (1);
	if ((*line)[0] == '>')
		return (1);
	if ((*line)[0] == '<')
		return (1);
	if ((*line)[0] == '|')
		return (1);
	return (0);
}

int	is_word(char **line)
{
	if (*line && (*line)[0] != ' ' && (*line)[0] != '\t'
		&& (*line)[0] != '|' && (*line)[0] != '<' && (*line)[0] != '>'
		&& (*line)[0] != '\0')
		return (1);
	return (0);
}
