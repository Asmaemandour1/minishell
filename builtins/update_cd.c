/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 07:01:15 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/21 06:41:42 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cd_update_value(t_env *env, char *new_value)
{
	char	*tmp;

	tmp = ft_strdup(new_value);
	free(env->value);
	free(new_value);
	env->value = tmp;
}

static void	cd_handle_update(t_env *env, char *value, int append)
{
	char	*new_value;

	if (append == 2)
	{
		new_value = ft_strdup(value);
		if (!new_value)
			return ;
		cd_update_value(env, new_value);
	}
}

void	update_cd_value(t_env **env, char *key, char *value, int append)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			cd_handle_update(tmp, value, append);
			free(value);
			return ;
		}
		tmp = tmp->next;
	}
	free(value);
}

int	update_cd_add(t_env **env, char *key, char *value, int append)
{
	if (check_key(*env, key))
	{
		(update_cd_value(env, key, value, append), free(key));
		return (1);
	}
	else
	{
		if (add_node_env(key, add_quotes(value), env) == 1)
			(free(key), free(value), exit_stat(0));
		return (free(value), 1);
	}
	return (0);
}

void	exit_st(int nbr)
{
	exit_stat(nbr);
	exit(nbr);
}
