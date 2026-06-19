/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:29:39 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/07/28 23:52:07 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/exec.h"

static int	check_dollar_in_quoted_section(char **line, int start_pos,
char quote)
{
	while ((*line)[start_pos] && (*line)[start_pos] != quote)
	{
		if ((*line)[start_pos] == '$')
			return (1);
		start_pos++;
	}
	return (0);
}

static char	*process_quoted_content(t_quote_context *ctx)
{
	if (ctx->quote == '\'' && ctx->has_dollar)
		ctx->word[(*ctx->j)++] = ctx->quote;
	while ((*ctx->line)[*ctx->i] && (*ctx->line)[*ctx->i] != ctx->quote)
		ctx->word[(*ctx->j)++] = (*ctx->line)[(*ctx->i)++];
	if ((*ctx->line)[*ctx->i] == ctx->quote)
	{
		if (ctx->quote == '\'' && ctx->has_dollar)
			ctx->word[(*ctx->j)++] = ctx->quote;
		(*ctx->i)++;
		return (ctx->word);
	}
	else
	{
		ft_putstr_fd("Syntax error: unclosed quotes\n", 2);
		free(ctx->word);
		*ctx->line += *ctx->i;
		return (NULL);
	}
}

char	*handle_quotes_in_word(char **line, char *word, int *i, int *j)
{
	t_quote_context	ctx;

	ctx.line = line;
	ctx.word = word;
	ctx.i = i;
	ctx.j = j;
	ctx.quote = (*line)[(*i)++];
	ctx.has_dollar = check_dollar_in_quoted_section(line, *i, ctx.quote);
	return (process_quoted_content(&ctx));
}
