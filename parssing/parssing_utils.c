/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:55:49 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/09 23:45:40 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_q_p(char *line)
{
	if (quotes(line) == -1 || check_pipes(line) == -1)
		return (-1);
	return (0);
}

int	handle_quotes(char *line, int limit, char *quote_char, int *in_quotes)
{
	int	j;

	j = 0;
	while (j < limit)
	{
		if ((line[j] == '\'' || line[j] == '"') && !(*in_quotes))
		{
			*quote_char = line[j];
			*in_quotes = 1;
		}
		else if (line[j] == *quote_char && *in_quotes)
			*in_quotes = 0;
		j++;
	}
	return (0);
}

int	check_red_out(char *line, int *i)
{
	char	quote_char;
	int		in_quotes;
	int		j;

	(1) && (quote_char = '\0', in_quotes = 0, j = 0);
	if (line[*i] == '>')
	{
		handle_quotes(line, *i, &quote_char, &in_quotes);
		if (in_quotes)
			return (0);
		if (line[*i + 1] == '>')
			(*i) += 2;
		else
			(*i)++;
		while (is_espace(line[*i]))
			(*i)++;
		if (line[*i] == '\0' || line[*i] == '|' || red(line[*i]))
			return (-1);
	}
	return (0);
}

int	check_red_in(char *line, int *i)
{
	char	quote_char;
	int		in_quotes;

	(1) && (quote_char = '\0', in_quotes = 0);
	if (line[*i] == '<')
	{
		handle_quotes(line, *i, &quote_char, &in_quotes);
		if (in_quotes)
			return (0);
		if (line[*i + 1] == '<')
			(*i) += 2;
		else
			(*i)++;
		while (is_espace(line[*i]))
			(*i)++;
		if (line[*i] == '\0' || line[*i] == '|' || red(line[*i]))
			return (-1);
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*niveau;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	niveau = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!niveau)
		return (NULL);
	while (s1[i] != '\0')
	{
		niveau[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		niveau[i] = s2[j];
		i++;
		j++;
	}
	niveau[i] = '\0';
	return (niveau);
}
