/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:01:50 by maalwis           #+#    #+#             */
/*   Updated: 2025/06/29 23:23:42 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_user_input(t_exec *exec)
{
	char	*input;

	setup_signal_main_shell();
	g_signal = SIG_NONE;
	input = readline(BLUE BOLD "Minishell" GREY BOLD " -> " RESET);
	if (g_signal == SIG_INTERRUPT)
	{
		exec->last_exit_status = SIG_INTERRUPT;
		g_signal = SIG_NONE;
	}
	if (!input)
		return (NULL);
	if (input[0] == '\0')
	{
		free(input);
		return (ft_strdup(""));
	}
	if (*input)
		add_history(input);
	return (input);
}

int	process_input(char *input, t_exec *exec, t_token **tokens)
{
	*tokens = NULL;
	identify_token(&input, tokens);
	if (!*tokens)
	{
		exec->last_exit_status = 2;
		return (0);
	}
	if (!validate_tokens(*tokens, exec))
	{
		free_tokens(*tokens);
		return (0);
	}
	return (1);
}

int	prepare_execution(t_token *tokens, t_cmd **cmds, t_exec *exec)
{
	*cmds = ft_calloc(1, sizeof(t_cmd));
	if (!*cmds)
	{
		free_tokens(tokens);
		return (0);
	}
	token_to_cmd(tokens, *cmds);
	exec->infile = STDIN_FILENO;
	exec->outfile = STDOUT_FILENO;
	exec->nb_cmds = 0;
	count_cmds(*cmds, exec);
	if (!*cmds)
	{
		free_cmd(*cmds);
		return (0);
	}
	if ((!(*cmds)->args || !(*cmds)->args[0]) && !(*cmds)->redirs)
	{
		free_cmd(*cmds);
		return (0);
	}
	return (1);
}

void	execute_shell_command(t_cmd *cmds, t_exec *exec, char **envp)
{
	int	has_pipe;
	int	has_redir;

	has_pipe = (cmds->next != NULL);
	has_redir = (cmds->redirs != NULL);
	if ((!cmds->args || !cmds->args[0]) && has_redir && !has_pipe)
	{
		handle_redirections_only(cmds, exec);
		return ;
	}
	if (is_builtin(cmds->args[0]) && !has_pipe && !has_redir)
	{
		expand_all_args(cmds, exec->last_exit_status);
		exec->last_exit_status = execute_builtin(cmds, envp,
				exec->last_exit_status);
	}
	else
		infinite_pipes(cmds, exec, envp);
}
