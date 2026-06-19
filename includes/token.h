/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:07:48 by maalwis           #+#    #+#             */
/*   Updated: 2025/06/29 23:20:53 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir_type
{
	char				*file;
	t_token_type		type;
	struct s_redir_type	*next;
}	t_redir_type;
typedef struct s_cmd
{
	char			**args;
	t_redir_type	*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_quote_context
{
	char	**line;
	char	*word;
	int		*i;
	int		*j;
	char	quote;
	int		has_dollar;
}	t_quote_context;

void				identify_token(char **line, t_token **tokens);
void				free_cmd(t_cmd *cmd);
void				free_tokens(t_token *token);
void				token_to_cmd(t_token *tokens, t_cmd *current);

t_token_type		get_token_type(char *line);
void				skip_space(char **line);
void				skip_quotes(char **line);
int					is_operator(char **line);
int					is_word(char **line);

char				*extract_operator(char **line);
int					count_args(char **tab);
char				*extract_word(char **line);
void				add_token(t_token **tokens, char *value, t_token_type type);

void				token_to_word(t_token *token, t_cmd *current);
void				token_to_operator(t_token *token, t_cmd *current);

char				*handle_quotes_in_word(char **line, char *word,
						int *i, int *j);

#endif
