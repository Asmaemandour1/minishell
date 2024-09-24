/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otuls_export_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 07:32:38 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/21 08:35:55 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_value(t_env *env, char *new_value)
{
	char	*tmp;

	tmp = add_quotes(new_value);
	free(env->value);
	free(new_value);
	env->value = tmp;
}

static void	append_to_value(t_env *env, char *value)
{
	char	*new_value;
	char	*temp;

	temp = remove_q(env->value);
	new_value = malloc(ft_strlen(temp) + ft_strlen(value) + 1);
	if (!new_value)
	{
		free(temp);
		return ;
	}
	ft_strcpy(new_value, temp);
	ft_strcat(new_value, value);
	free(temp);
	update_value(env, new_value);
}

static void	handle_update(t_env *env, char *value, int append)
{
	char	*new_value;

	if (append == 1)
		append_to_value(env, value);
	if (append == 2)
	{
		new_value = ft_strdup(value);
		if (!new_value)
			return ;
		update_value(env, new_value);
	}
}

void	update_env_value(t_env **env, char *key, char *value, int append)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			handle_update(tmp, value, append);
			free(value);
			return ;
		}
		tmp = tmp->next;
	}
	free(value);
}

void	handle_error(char *f_key, char *f_value)
{
	(free(f_key), free(f_value), exit_stat(1));
	return ;
}
