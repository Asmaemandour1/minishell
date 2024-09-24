/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandour <amandour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:43:27 by amandour          #+#    #+#             */
/*   Updated: 2024/09/11 21:43:28 by amandour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

void	free_str_tab(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**env_to_tab(t_env *env)
{
	char	**env_tab;
	int		size;
	int		i;
	int		value_len;
	int		name_len;

	(1) && (size = get_env_size(env), i = 0);
	env_tab = malloc((size + 1) * sizeof(char *));
	if (!env_tab)
		return (perror("malloc"), NULL);
	while (env)
	{
		name_len = ft_strlen(env->key);
		value_len = ft_strlen(env->value);
		env_tab[i] = malloc((name_len + value_len + 2) * sizeof(char));
		if (!env_tab[i])
			return (perror("malloc"), free_str_tab(env_tab), NULL);
		ft_strcpy(env_tab[i], env->key);
		ft_strcat(env_tab[i], "=");
		ft_strcat(env_tab[i], env->value);
		i++;
		env = env->next;
	}
	env_tab[i] = NULL;
	return (env_tab);
}
