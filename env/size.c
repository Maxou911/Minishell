/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 23:27:48 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/06/28 00:02:15 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_exit_status_size(int last_exit_status)
{
	char	*value;
	int		size;

	value = ft_itoa(last_exit_status);
	if (!value)
		return (0);
	size = ft_strlen(value);
	free(value);
	return (size);
}

static int	get_env_var_size(char *str, int *i)
{
	char	*var_name;
	char	*value;
	int		var_start;
	int		size;

	var_start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, var_start, *i - var_start);
	if (!var_name)
		return (0);
	value = getenv(var_name);
	size = 0;
	if (value)
		size = ft_strlen(value);
	free(var_name);
	return (size);
}

static int	process_dollar_expansion(char *str, int *i, int last_exit_status)
{
	if (str[*i + 1] == '?')
	{
		*i += 2;
		return (get_exit_status_size(last_exit_status));
	}
	else if (str[*i + 1] && (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_'))
	{
		(*i)++;
		return (get_env_var_size(str, i));
	}
	else
	{
		(*i)++;
		return (1);
	}
}

char	*calculate_expanded_size(char *str, int last_exit_status)
{
	int	i;
	int	total_size;

	i = 0;
	total_size = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
		{
			total_size += process_dollar_expansion(str, &i, last_exit_status);
		}
		else
		{
			total_size++;
			i++;
		}
	}
	return (malloc(sizeof(char) * (total_size + 1)));
}
