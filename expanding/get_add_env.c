/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_add_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:50:07 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/11 22:50:08 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_l_node_(t_env *last)
{
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

int	add_node_env(char *key, char *value, t_env **env)
{
	t_env	*node;
	t_env	*l_node;

	if (!key)
		return (free(value), 1);
	node = malloc(sizeof(t_env));
	if (!node)
		return (free(key), free(value), 1);
	node->key = key;
	node->next = NULL;
	node->value = value;
	if (!(*env))
		*env = node;
	else
	{
		l_node = find_l_node_(*env);
		l_node->next = node;
	}
	return (0);
}

int	ft_get_env(char **env, t_env **envt)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (env[i])
	{
		key = get_env_key(env[i]);
		if (!key)
			return (-1);
		value = get_env_value(env[i]);
		if (!value)
			return (free(key), -1);
		if (add_node_env(key, value, envt))
			return (free(key), free(value), -1);
		i++;
	}
	return (0);
}

char	*get_env_value_by_key(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*skip_single_quote(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr == '\'')
		{
			ptr++;
			while (*ptr && *ptr != '\'')
				ptr++;
			if (*ptr == '\'')
				ptr++;
			else
				break ;
		}
		else
			ptr++;
	}
	return (ptr);
}
