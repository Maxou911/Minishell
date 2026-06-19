/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:20:00 by uzyberaj          #+#    #+#             */
/*   Updated: 2025/06/27 23:25:13 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_echo_args(char **args, int start_index)
{
	int		i;
	char	*arg;

	i = start_index;
	while (args[i])
	{
		arg = args[i];
		if (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'')
		{
			arg = ft_substr(arg, 1, ft_strlen(arg) - 2);
			if (!arg)
				return ;
		}
		ft_putstr_fd(arg, 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	ft_echo(char **args)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	while (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
	{
		n_flag = 1;
		i++;
	}
	print_echo_args(args, i);
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (0);
}
