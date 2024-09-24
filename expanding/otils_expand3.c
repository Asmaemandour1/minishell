/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otils_expand3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:42:11 by amandour          #+#    #+#             */
/*   Updated: 2024/09/20 23:17:38 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(char *src, int n)
{
	char	*new;
	int		i;
	int		len;

	len = 0;
	while (src[len] && len < n)
		++len;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	is_single_quotes(char *str, char *pos)
{
	char	*current;
	int		s_quote;
	int		d_quote;

	(1) && (current = str, s_quote = 0, d_quote = 0);
	while (current < pos)
	{
		if (*current == '"' && !s_quote)
			d_quote = !d_quote;
		else if (*current == '\'' && !d_quote)
			s_quote = !s_quote;
		current++;
	}
	if (s_quote)
		return (1);
	return (0);
}

int	compare_pos1(char *str)
{
	int	pos_equal;
	int	pos_dollar;
	int	i;

	(1) && (pos_equal = -1, pos_dollar = -1, i = 0);
	while (str[i] != '\0')
	{
		if (str[i] == '=' && pos_equal == -1)
			pos_equal = i;
		if (str[i] == '$' && pos_dollar == -1)
			pos_dollar = i;
		i++;
	}
	if (pos_equal == -1 || pos_dollar == -1)
		return (1);
	if (pos_equal < pos_dollar)
		return (0);
	else
		return (1);
}

int	is_wildcard_quoted(char *str)
{
	int		s_quote;
	int		d_quote;
	int		i;

	(1) && (s_quote = 0, d_quote = 0, i = 0);
	while (str[i])
	{
		if (str[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (str[i] == '"' && !s_quote)
			d_quote = !d_quote;
		else if (str[i] == '*' && !s_quote && !d_quote)
			return (0);
		i++;
	}
	return (1);
}
