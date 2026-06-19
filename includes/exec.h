/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:27:31 by maalwis           #+#    #+#             */
/*   Updated: 2025/06/28 00:34:27 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "token.h"
# include "../superlibft/includes/superlibft.h"
# include <sys/types.h>

typedef struct s_exec
{
	int		infile;
	int		outfile;
	int		pipe_fd[2];
	int		prev_fd;
	int		index;
	int		i;
	int		nb_cmds;
	int		cmd_start_index;
	int		exit_status;
	int		last_exit_status;
	int		in_heredoc;
	pid_t	*pid;
}	t_exec;

typedef struct s_expand_ctx
{
	char	*str;
	char	*new_str;
	int		*i;
	int		*j;
	int		last_exit_status;
}	t_expand_ctx;

//validation_token
int		validate_tokens(t_token *tokens, t_exec *exec);

//execute_command
void	execute_command(t_cmd *cmd, char **envp);

// free_split
void	free_split(char **split);

// cmd_path
char	*cmd_path(char **path, char *cmd);
char	*search_path(char **envp);

// multiple pipes
void	infinite_pipes(t_cmd *cmd, t_exec *exec, char **envp);
void	safe_dup2(int oldfd, int newfd);
void	parent_process(t_exec *exec);

// handle heredoc
int		handle_heredoc(t_exec *exec, t_redir_type *redir);
int		setup_heredoc_pipe(int *heredoc_pipe);
int		read_heredoc_line(t_redir_type *redir, int write_fd);
int		read_heredoc_input(t_redir_type *redir, int write_fd);
int		handle_heredoc_child_process(t_redir_type *redir, int *heredoc_pipe);
int		handle_heredoc_parent_process(t_exec *exec, int *heredoc_pipe,
			pid_t pid);

// close_fd
void	close_fd(t_exec *exec);

//redirections
int		handle_redirections(t_redir_type *redir, t_exec *exec);

//nb de commandes
int		count_cmds(t_cmd *cmd, t_exec *exec);

// variables d'environnement
char	*extract_var_name(char *str, int *i);
void	append_value_env(char *new_str, int *j, char *var_name);
void	append_exit_value(char *new_str, int *j, int last_exit_status);
int		single_quotes_even_or_odd(char *line, int dollar_index);
char	*expand_variable(char *str, int last_exit_status);
void	handle_exit_status(t_expand_ctx *ctx);
void	handle_env_var(t_expand_ctx *ctx);
void	process_variable(t_expand_ctx *ctx);
void	expand_all_args(t_cmd *cmd, int last_exit_status);
void	child_process(t_cmd *cmd, t_exec *exec, char **envp);
void	setup_redirections(t_cmd *cmd, t_exec *exec, int *local_in,
			int *local_out);
void	apply_redirections(t_exec *exec, int local_in, int local_out);

#endif
