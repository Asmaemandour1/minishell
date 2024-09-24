/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_espace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:28:06 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/21 08:30:32 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_q(char c, int *s_quote, int *d_quote)
{
	if (c == '\'')
		*s_quote = !(*s_quote);
	else if (c == '"')
		*d_quote = !(*d_quote);
}

int	calcul_new_len(char *line)
{
	int	len;
	int	new_len;
	int	i;
	int	s_quote;
	int	d_quote;

	(1) && (len = ft_strlen(line), new_len = len,
		i = 0, s_quote = 0, d_quote = 0);
	while (i < len)
	{
		update_q(line[i], &s_quote, &d_quote);
		if ((line[i] == '>' || line[i] == '<' || line[i] == '|') && \
			!s_quote && !d_quote)
		{
			if (i > 0 && !is_espace(line[i - 1]))
				new_len++;
			if (i < len - 1 && !is_espace(line[i + 1]))
				new_len++;
		}
		i++;
	}
	return (new_len);
}

void	add_space_red(char *line, char *newline, int *i, int *j)
{
	if (*i > 0 && !is_espace(line[*i - 1]))
		newline[(*j)++] = ' ';
	newline[(*j)++] = line[*i];
	if ((line[*i] == '>' && line[*i + 1] == '>') || \
		(line[*i] == '<' && line[*i + 1] == '<'))
		newline[(*j)++] = line[++(*i)];
	if (line[*i + 1] && !is_espace(line[*i + 1]))
		newline[(*j)++] = ' ';
}

void	add_spaces(char *line, char *newline)
{
	int	i;
	int	j;
	int	s_quote;
	int	d_quote;

	i = 0;
	j = 0;
	s_quote = 0;
	d_quote = 0;
	while (line[i])
	{
		update_q(line[i], &s_quote, &d_quote);
		if ((line[i] == '<' || line[i] == '>' || line[i] == '|') && \
			!s_quote && !d_quote)
			add_space_red(line, newline, &i, &j);
		else
			newline[j++] = line[i];
		i++;
	}
	newline[j] = '\0';
}

char	*add_espace(char *line)
{
	int		new_len;
	char	*newline;

	new_len = calcul_new_len(line);
	newline = (char *)malloc(new_len + 1);
	if (!newline)
	{
		perror("error in malloc ");
		exit(1);
	}
	add_spaces(line, newline);
	free(line);
	return (newline);
}
