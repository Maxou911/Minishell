/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:21:25 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/06/27 23:27:37 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*init_expand_context(char *str, int last_exit_status,
t_expand_ctx *ctx)
{
	char	*new_str;

	new_str = calculate_expanded_size(str, last_exit_status);
	if (!new_str)
		return (NULL);
	ctx->str = str;
	ctx->new_str = new_str;
	ctx->last_exit_status = last_exit_status;
	return (new_str);
}

static void	handle_single_quote(t_expand_ctx *ctx, int *i, int *j,
int *in_single_quotes)
{
	*in_single_quotes = !(*in_single_quotes);
	ctx->new_str[*j] = ctx->str[*i];
	(*j)++;
	(*i)++;
}

static void	handle_dollar_sign(t_expand_ctx *ctx, int *i, int *j)
{
	if (!ctx->str[*i + 1] || (!ft_isalnum(ctx->str[*i + 1])
			&& ctx->str[*i + 1] != '_' && ctx->str[*i + 1] != '?'))
	{
		ctx->new_str[*j] = ctx->str[*i];
		(*j)++;
		(*i)++;
		return ;
	}
	ctx->i = i;
	ctx->j = j;
	process_variable(ctx);
}

static void	process_expansion_loop(t_expand_ctx *ctx, int *i, int *j)
{
	int	in_single_quotes;

	in_single_quotes = 0;
	while (ctx->str[*i])
	{
		if (ctx->str[*i] == '\'')
			handle_single_quote(ctx, i, j, &in_single_quotes);
		else if (ctx->str[*i] == '$' && !in_single_quotes)
			handle_dollar_sign(ctx, i, j);
		else
		{
			ctx->new_str[*j] = ctx->str[*i];
			(*j)++;
			(*i)++;
		}
	}
	ctx->new_str[*j] = '\0';
}

char	*expand_variable(char *str, int last_exit_status)
{
	t_expand_ctx	ctx;
	char			*new_str;
	int				i;
	int				j;

	new_str = init_expand_context(str, last_exit_status, &ctx);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	process_expansion_loop(&ctx, &i, &j);
	return (new_str);
}
