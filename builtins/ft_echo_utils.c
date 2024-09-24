/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:17:40 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/09 04:40:35 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	count_q(char *str)
{
	size_t	cpt;
	int		s_quote;
	int		d_quote;

	(1) && (d_quote = 0, s_quote = 0, cpt = 0);
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\'' && !d_quote)
		{
			s_quote = !s_quote;
			cpt++;
		}
		else if (*str == '"' && !s_quote)
		{
			d_quote = !d_quote;
			cpt++;
		}
		str++;
	}
	return (cpt);
}

static int	update_quotes(char c, int *d_quote, int *s_quote)
{
	if (c == '\'' && !*d_quote)
	{
		*s_quote = !*s_quote;
		return (1);
	}
	if (c == '"' && !*s_quote)
	{
		*d_quote = !*d_quote;
		return (1);
	}
	return (0);
}

void	handl_seul_q(char *res, size_t *j, int s_quote, int d_quote)
{
	if (s_quote)
		res[(*j)++] = '\'';
	else if (d_quote)
		res[(*j)++] = '"';
}

char	*remove_q(char *str)
{
	char	*res;
	size_t	i;
	size_t	j;
	int		d_quote;
	int		s_quote;

	(1) && (d_quote = 0, s_quote = 0, i = 0, j = 0);
	res = (char *)malloc(ft_strlen(str) - count_q(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (update_quotes(str[i], &d_quote, &s_quote))
		{
			i++;
			continue ;
		}
		res[j++] = str[i++];
	}
	handl_seul_q(res, &j, s_quote, d_quote);
	res[j] = '\0';
	return (res);
}
