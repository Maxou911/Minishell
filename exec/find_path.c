/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:17:16 by maalwis           #+#    #+#             */
/*   Updated: 2025/07/28 21:22:41 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*search_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*cmd_path(char **path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	*resolve_exec_path(t_cmd *cmd, char **envp)
{
	char	*path;
	char	**paths_splitted;
	char	*exec_path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (NULL);
	path = search_path(envp);
	if (!path)
	{
		ft_putstr_fd("Error : PATH not found\n", 2);
		exit (127);
	}
	paths_splitted = ft_split(path, ':');
	if (!paths_splitted)
		(free_split(paths_splitted), exit (1));
	exec_path = cmd_path(paths_splitted, cmd->args[0]);
	if (!exec_path)
	{
		free_split(paths_splitted);
		ft_putstr_fd("Error : Command not found\n", 2);
		exit (127);
	}
	return (free_split(paths_splitted), exec_path);
}

void	execute_command(t_cmd *cmd, char **envp)
{
	char	*exec_path;
	int		exit_code;

	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
	{
		exit_code = execute_builtin(cmd, envp, 0);
		exit(exit_code);
	}
	exec_path = resolve_exec_path(cmd, envp);
	if (!exec_path || !cmd->args || !cmd->args[0])
		return ;
	if (execve(exec_path, cmd->args, envp) == -1)
	{
		perror("execve");
		free(exec_path);
		exit (126);
	}
	exit (1);
}
