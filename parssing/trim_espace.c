/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_espace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 01:49:14 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/11 01:49:17 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_espace(char c)
{
	return (c == ' ' || c == '\t');
}

char	*trim_espace(char *str)
{
	char	*start;
	char	*end;
	char	*trimmed;

	if (!str)
		return (NULL);
	start = str;
	while (is_espace(*start))
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	end = start + ft_strlen(start) - 1;
	while (end > start && is_espace(*end))
		end--;
	end[1] = '\0';
	trimmed = ft_strdup(start);
	return (trimmed);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
