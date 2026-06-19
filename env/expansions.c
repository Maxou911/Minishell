/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:34:27 by maalwis           #+#    #+#             */
/*   Updated: 2025/06/26 18:14:38 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_var_name(char *str, int *i)
{
	char	*var_name;
	int		j;

	j = 0;
	var_name = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!var_name)
		return (NULL);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		var_name[j++] = str[(*i)++];
	var_name[j] = '\0';
	return (var_name);
}

void	append_value_env(char *new_str, int *j, char *var_name)
{
	char	*value;
	int		k;

	k = 0;
	if (!var_name || !*var_name)
		return ;
	value = getenv(var_name);
	if (value)
	{
		while (value[k])
			new_str[(*j)++] = value[k++];
	}
}

void	append_exit_value(char *new_str, int *j, int last_exit_status)
{
	char	*value;
	int		k;

	k = 0;
	value = ft_itoa(last_exit_status);
	if (value)
	{
		while (value[k])
			new_str[(*j)++] = value[k++];
		free(value);
	}
}

int	single_quotes_even_or_odd(char *line, int dollar_index)
{
	int	i;
	int	count_quotes;

	i = 0;
	count_quotes = 0;
	while (line[i] && i < dollar_index)
	{
		if (line[i] == '\'')
			count_quotes++;
		i++;
	}
	return (count_quotes % 2 == 0);
}

void	expand_all_args(t_cmd *cmd, int last_exit_status)
{
	int		i;
	char	*expanded;

	while (cmd)
	{
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			expanded = expand_variable(cmd->args[i], last_exit_status);
			if (expanded)
			{
				free(cmd->args[i]);
				cmd->args[i] = expanded;
			}
			i++;
		}
		cmd = cmd->next;
	}
}
