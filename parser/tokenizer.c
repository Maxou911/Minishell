/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:10:15 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/06/27 17:29:33 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/exec.h"

char	*extract_operator(char **line)
{
	if ((*line)[0] == '>' && (*line)[1] == '>')
		return ((*line) += 2, ft_strdup(">>"));
	if ((*line)[0] == '<' && (*line)[1] == '<')
		return ((*line) += 2, ft_strdup("<<"));
	if ((*line)[0] == '>')
		return ((*line) += 1, ft_strdup(">"));
	if ((*line)[0] == '<')
		return ((*line) += 1, ft_strdup("<"));
	if ((*line)[0] == '|')
		return ((*line) += 1, ft_strdup("|"));
	return (NULL);
}

int	count_args(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

char	*extract_word(char **line)
{
	char	*word;
	int		i;
	int		j;

	word = malloc(sizeof(char) * (ft_strlen(*line) + 1));
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	while ((*line)[i] && !((*line)[i] == ' ' || (*line)[i] == '\t'))
	{
		if ((*line)[i] == '\'' || (*line)[i] == '\"')
		{
			word = handle_quotes_in_word(line, word, &i, &j);
			if (!word)
				return (NULL);
		}
		else if ((*line)[i] == '|' || (*line)[i] == '<' || (*line)[i] == '>')
		{
			break ;
		}
		else
			word[j++] = (*line)[i++];
	}
	return (word[j] = '\0',*line += i, word);
}

void	add_token(t_token **tokens, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = ft_strdup(value);
	new->type = type;
	new->next = NULL;
	if (!*tokens)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
