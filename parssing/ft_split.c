/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:35:07 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/10 01:30:58 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_space(t_split *ctx)
{
	if (ctx->n > 0)
	{
		ctx->buff[ctx->n] = '\0';
		ctx->result[ctx->j] = ft_strdup(ctx->buff);
		if (!ctx->result[ctx->j])
		{
			free(ctx->buff);
			ft_free(ctx->result);
			exit(1);
		}
		ctx->j++;
		ctx->n = 0;
	}
}

void	process_character(char c, t_split *ctx)
{
	if (c == '\'' && !ctx->d_quote)
	{
		ctx->s_quote = !ctx->s_quote;
		ctx->buff[ctx->n++] = c;
	}
	else if (c == '"' && !ctx->s_quote)
	{
		ctx->d_quote = !ctx->d_quote;
		ctx->buff[ctx->n++] = c;
	}
	else if (c == ' ' && !ctx->s_quote && !ctx->d_quote)
		handle_space(ctx);
	else
		ctx->buff[ctx->n++] = c;
}

void	finalize_split(t_split *ctx)
{
	if (ctx->n > 0)
	{
		ctx->buff[ctx->n] = '\0';
		ctx->result[ctx->j] = ft_strdup(ctx->buff);
		if (!ctx->result[ctx->j])
		{
			free(ctx->buff);
			ft_free(ctx->result);
			exit(1);
		}
		ctx->j++;
	}
	ctx->result[ctx->j] = NULL;
	free(ctx->buff);
}

int	init_split(t_split *ctx, char *str, int result_size)
{
	ctx->buff = (char *)malloc(ft_strlen(str) + 1);
	if (!ctx->buff)
		return (0);
	ctx->result = (char **)malloc((result_size + 1) * sizeof(char *));
	if (!ctx->result)
		return (free(ctx->buff), 0);
	ctx->i = 0;
	ctx->j = 0;
	ctx->n = 0;
	ctx->s_quote = 0;
	ctx->d_quote = 0;
	return (1);
}

char	**ft_split(char *str)
{
	t_split	ctx;
	int		c;

	c = count_w_test(str);
	if (!init_split(&ctx, str, c))
		return (NULL);
	while (str[ctx.i])
		process_character(str[ctx.i++], &ctx);
	finalize_split(&ctx);
	return (ctx.result);
}
