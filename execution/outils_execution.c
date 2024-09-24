/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandour <amandour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:11:22 by amandour          #+#    #+#             */
/*   Updated: 2024/09/11 14:11:25 by amandour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_w(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static char	*ft_words(char const *str, int n)
{
	int		i;
	char	*niveau;

	i = 0;
	niveau = (char *)malloc(n + 1);
	if (niveau == NULL)
		return (NULL);
	while (i < n)
	{
		niveau[i] = str[i];
		i++;
	}
	niveau[i] = '\0';
	return (niveau);
}

char	**ft_freee(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	**splite(char const *str, char c)
{
	int		i;
	int		j;
	int		taille;
	char	**strs;

	taille = ft_count_w(str, c);
	strs = (char **)malloc((sizeof(char *)) * (taille + 1));
	if (!strs)
		return (NULL);
	j = -1;
	while (++j < taille)
	{
		i = 0;
		while (*str == c && *str)
			str++;
		while (*(str + i) != c && *(str + i))
			i++;
		strs[j] = ft_words(str, i);
		if (!strs[j])
			return (ft_freee(strs));
		while (*str != c && *str)
			str++;
	}
	strs[j] = 0;
	return (strs);
}
