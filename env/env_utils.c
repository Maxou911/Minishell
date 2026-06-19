/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:20:42 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/07/29 16:51:47 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_env_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static char	**allocate_and_copy_env(char **envp, int count)
{
	int		i;
	int		j;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (count + 101));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			j = 0;
			while (j < i)
				free(new_env[j++]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**copy_env(char **envp)
{
	int		count;

	count = count_env_vars(envp);
	return (allocate_and_copy_env(envp, count));
}
