/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:48:38 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/21 08:44:07 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	red(char c)
{
	return (c == '>' || c == '<');
}

int	ft_parsing(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	if (check_q_p(line) == -1)
		return (-1);
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (i == 0 || line[i + 1] == '\0')
				return (-1);
		}
		if (line[len - 1] == '|' && len > 0)
			return (-1);
		if (check_red_out(line, &i) == -1)
			return (-1);
		if (check_red_in(line, &i) == -1)
			return (-1);
		i++;
	}
	return (1);
}

char	*ft_strstr(char *src, char *rech)
{
	int	i;
	int	j;

	i = 0;
	if (rech[0] == '\0')
		return (src);
	while (src[i] != '\0')
	{
		j = 0;
		while (src[i + j] != '\0' && src[i + j] == rech[j])
		{
			if (rech[j + 1] == '\0')
				return (&src[i]);
			++j;
		}
		++i;
	}
	return (0);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*niveau;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(s2));
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
