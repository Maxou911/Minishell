/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:46:09 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/06/10 17:46:12 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	print_exit_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

static void	print_too_many_args(void)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
}

int	ft_exit(char **args, int last_exit_status)
{
	int	exit_code;

	if (!args[1])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(last_exit_status);
	}
	if (!is_numeric(args[1]))
	{
		print_exit_error(args[1]);
		exit(255);
	}
	if (args[2])
	{
		print_too_many_args();
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(exit_code);
}
