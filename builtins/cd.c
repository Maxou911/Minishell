/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:06:47 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/06/26 17:34:44 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s || fd < 0)
		return ;
	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

static int	update_pwd(void)
{
	char	*cwd;
	char	*old_pwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	old_pwd = getenv("PWD");
	if (old_pwd)
		setenv("OLDPWD", old_pwd, 1);
	setenv("PWD", cwd, 1);
	free(cwd);
	return (0);
}

static int	handle_cd_minus(void)
{
	char	*old_pwd;

	old_pwd = getenv("OLDPWD");
	if (!old_pwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (chdir(old_pwd) == -1)
	{
		perror("cd");
		return (1);
	}
	ft_putstr_fd(old_pwd, 1);
	ft_putstr_fd("\n", 1);
	return (update_pwd());
}

static int	handle_cd_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		return (1);
	}
	return (update_pwd());
}

int	ft_cd(char **args)
{
	if (!args[1] || (args[1][0] == '~' && !args[1][1]))
		return (handle_cd_home());
	if (args[1][0] == '-' && !args[1][1])
		return (handle_cd_minus());
	if (args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		return (1);
	}
	return (update_pwd());
}
