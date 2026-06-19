/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:30:00 by uzyberaj          #+#    #+#             */
/*   Updated: 2025/06/26 18:22:30 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_exit_status(t_expand_ctx *ctx)
{
	*(ctx->i) += 2;
	append_exit_value(ctx->new_str, ctx->j, ctx->last_exit_status);
}

void	handle_env_var(t_expand_ctx *ctx)
{
	char	*var_name;

	(*(ctx->i))++;
	var_name = extract_var_name(ctx->str, ctx->i);
	append_value_env(ctx->new_str, ctx->j, var_name);
	free(var_name);
}

void	process_variable(t_expand_ctx *ctx)
{
	if (ctx->str[*(ctx->i) + 1] == '?')
		handle_exit_status(ctx);
	else if (ctx->str[*(ctx->i) + 1]
		&& (ft_isalnum(ctx->str[*(ctx->i) + 1])
			|| ctx->str[*(ctx->i) + 1] == '_'))
		handle_env_var(ctx);
	else
	{
		ctx->new_str[*(ctx->j)++] = ctx->str[*(ctx->i)++];
	}
}
