/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otuls_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandour <amandour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 06:41:04 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/11 19:47:38 by amandour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_key(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

char	*get_env_value(char *env_line)
{
	char	*value;
	int		len;
	int		i;

	len = 0;
	while (env_line[len] && env_line[len] != '=' && \
		!(env_line[len] == '+' && env_line[len + 1] == '='))
		len++;
	if (env_line[len] == '\0')
		return (NULL);
	if (env_line[len] == '=')
		len++;
	else if (env_line[len] == '+' && env_line[len + 1] == '=')
		len += 2;
	value = malloc(sizeof(char) * (ft_strlen(env_line) - len + 1));
	if (!value)
		return (NULL);
	i = 0;
	while (env_line[len])
	{
		value[i] = env_line[len];
		(1) && (i++, len++);
	}
	value[i] = '\0';
	return (value);
}

char	*get_env_key(char *env_line)
{
	char	*key;
	int		i;
	int		j;

	(1) && (key = NULL, i = 0, j = 0);
	while (env_line[i] && env_line[i] != '=' && \
		!(env_line[i] == '+' && env_line[i + 1] == '='))
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	while (j < i)
	{
		key[j] = env_line[j];
		j++;
	}
	key[j] = 0;
	return (key);
}

void	display_env2(t_env *list)
{
	while (list)
	{
		printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
}

void	display_env(t_env *list)
{
	while (list)
	{
		if (list->value == NULL || list->value[0] == '\0')
			printf("declare -x %s\n", (list->key));
		else
			printf("declare -x %s=%s\n", list->key, list->value);
		list = list->next;
	}
}
