/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:43:53 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/06/26 15:35:28 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	cleanup_and_continue(char *input, t_token *tokens, t_cmd *cmds)
{
	free_tokens(tokens);
	free_cmd(cmds);
	free(input);
}

static int	process_command(char *input, t_exec *exec, char **envp)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (!process_input(input, exec, &tokens))
	{
		free(input);
		return (0);
	}
	if (!prepare_execution(tokens, &cmds, exec))
	{
		free(input);
		return (0);
	}
	execute_shell_command(cmds, exec, envp);
	cleanup_and_continue(input, tokens, cmds);
	return (1);
}

static char	**init_environment(char **envp)
{
	char	**my_env;

	my_env = copy_env(envp);
	if (!my_env)
	{
		ft_putstr_fd("Erreur d'allocation de l'environnement\n", 2);
		return (NULL);
	}
	return (my_env);
}

static void	cleanup_environment(char **my_env)
{
	int	i;

	i = 0;
	while (my_env[i])
		free(my_env[i++]);
	free(my_env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_exec	exec;
	char	**my_env;

	(void)argc;
	(void)argv;
	my_env = init_environment(envp);
	if (!my_env)
		return (1);
	exec.last_exit_status = 0;
	while (1)
	{
		input = get_user_input(&exec);
		if (!input)
			break ;
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		process_command(input, &exec, my_env);
	}
	cleanup_environment(my_env);
	return (0);
}
