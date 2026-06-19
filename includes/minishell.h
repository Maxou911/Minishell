/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:56:04 by maalwis           #+#    #+#             */
/*   Updated: 2025/06/28 00:16:23 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "token.h"
# include "exec.h"
# include "../superlibft/includes/superlibft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>

extern volatile sig_atomic_t	g_signal;

# define BOLD    "\001\033[1m\002"
# define RESET   "\001\033[0m\002"
# define BLUE    "\001\033[38;5;111m\002"
# define GREY    "\001\033[38;5;231m\002"

# define SIG_NONE        0
# define SIG_INTERRUPT   130
# define SIG_HEREDOC     2

// main utils
char	*get_user_input(t_exec *exec);
int		process_input(char *input, t_exec *exec, t_token **tokens);
int		prepare_execution(t_token *tokens, t_cmd **cmds, t_exec *exec);
void	execute_shell_command(t_cmd *cmds, t_exec *exec, char **envp);
void	handle_redirections_only(t_cmd *cmds, t_exec *exec);

// signals
void	setup_signal_main_shell(void);
void	ignore_sigint(void);
void	reset_signals_child(void);
void	set_signals_heredoc_child(void);
void	set_signals_heredoc_parent(void);

// exec builtins
int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, char **env, int last_exit_status);

// builtins
int		ft_cd(char **args);
void	print_current_dir(void);
int		ft_pwd(void);
int		ft_echo(char **args);
int		ft_env(char **args, char **env);
int		ft_export(char **args, char **env);
int		export_var(char *arg, char **env);
int		ft_unset(char **args, char **env);
int		ft_exit(char **args, int last_exit_status);

// env
char	**copy_env(char **envp);

char	*calculate_expanded_size(char *str, int last_exit_status);

#endif
