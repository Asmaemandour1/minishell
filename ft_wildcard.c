/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:03:32 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/17 14:25:37 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_words(char **words)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (words[i])
	{
		j = i + 1;
		while (words[j])
		{
			if (ft_strcmp(words[i], words[j]) > 0)
			{
				temp = words[j];
				words[j] = words[i];
				words[i] = temp;
			}
			j++;
		}
		i++;
	}
}

static char	*concatenate_words(char **words)
{
	char	*result;
	char	*temp;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (words[i])
	{
		temp = ft_strjoin1(result, words[i]);
		free(result);
		result = temp;
		temp = ft_strjoin1(result, " ");
		free(result);
		result = temp;
		i++;
	}
	if (ft_strlen(result) > 0)
		result[ft_strlen(result) - 1] = '\0';
	return (result);
}

char	*sort_wildcard(char *dir)
{
	char	**words;
	char	*sorted_result;
	int		i;

	words = splite(dir, ' ');
	free(dir);
	if (!words)
		return (NULL);
	sort_words(words);
	sorted_result = concatenate_words(words);
	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (sorted_result);
}

int	match_wildcard(char *pattern, char *filename)
{
	char	*p;
	char	*f;
	char	*wildcard;
	char	*after_wildcard;

	(1) && (wildcard = NULL, after_wildcard = NULL);
	(1) && (p = pattern, f = filename);
	while (*f)
	{
		if (*p == '*')
			(1) && (wildcard = p++, after_wildcard = f);
		else if (*p == *f)
			(1) && (p++, f++);
		else if (wildcard)
			(1) && (p = wildcard + 1, f = ++after_wildcard);
		else
			return (0);
	}
	while (*p == '*')
		p++;
	return (*p == '\0');
}

char	*ft_wildcard(char *pattern)
{
	struct dirent	*entry;
	DIR				*dir;
	char			*result;
	char			*tmp_r;

	(1) && (dir = opendir("."), result = NULL);
	if (!dir)
		return (NULL);
	(1) && (result = ft_strdup(""), entry = readdir(dir));
	while (entry)
	{
		if (ft_strncmp(entry->d_name, ".", 1) == 0)
		{
			entry = readdir(dir);
			continue ;
		}
		else if (match_wildcard(pattern, entry->d_name))
		{
			tmp_r = ft_strjoin1(result, entry->d_name);
			(free(result), result = ft_strjoin1(tmp_r, " "));
			free(tmp_r);
		}
		entry = readdir(dir);
	}
	return (closedir(dir), sort_wildcard(result));
}
