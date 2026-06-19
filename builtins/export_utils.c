/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:00:00 by uzyberaj          #+#    #+#             */
/*   Updated: 2025/07/29 17:04:00 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	update_existing_var(char *name, char *arg, char **env, int i)
{
	char	*equals_pos;

	free(env[i]);
	env[i] = ft_strdup(arg);
	if (!env[i])
	{
		free(name);
		return (1);
	}
	equals_pos = ft_strchr(arg, '=');
	if (equals_pos)
	{
		*equals_pos = '\0';
		if (setenv(arg, equals_pos + 1, 1) == -1)
		{
			*equals_pos = '=';
			free(name);
			return (1);
		}
		*equals_pos = '=';
	}
	free(name);
	return (0);
}

static int	check_limits_and_add_to_env_array(char *name, char *arg,
	char **env, int i)
{
	int	total_vars;

	total_vars = 0;
	while (env[total_vars])
		total_vars++;
	if (total_vars >= 99)
	{
		ft_putstr_fd("minishell: export: too many environment variables\n",
			STDERR_FILENO);
		free(name);
		return (1);
	}
	env[i] = ft_strdup(arg);
	if (!env[i])
	{
		free(name);
		return (1);
	}
	env[i + 1] = NULL;
	return (0);
}

static int	add_new_var(char *name, char *arg, char **env, int i)
{
	char	*equals_pos;

	if (check_limits_and_add_to_env_array(name, arg, env, i))
		return (1);
	equals_pos = ft_strchr(arg, '=');
	if (equals_pos)
	{
		*equals_pos = '\0';
		if (setenv(arg, equals_pos + 1, 1) == -1)
		{
			*equals_pos = '=';
			free(env[i]);
			env[i] = NULL;
			free(name);
			return (1);
		}
		*equals_pos = '=';
	}
	free(name);
	return (0);
}

static int	find_and_update_var(char *name, char *arg, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0
			&& env[i][ft_strlen(name)] == '=')
		{
			return (update_existing_var(name, arg, env, i));
		}
		i++;
	}
	return (add_new_var(name, arg, env, i));
}

int	export_var(char *arg, char **env)
{
	char	*name;
	char	*value;

	if (!ft_strchr(arg, '='))
		return (0);
	name = ft_strdup(arg);
	if (!name)
		return (1);
	value = ft_strchr(name, '=');
	*value = '\0';
	value++;
	return (find_and_update_var(name, arg, env));
}
