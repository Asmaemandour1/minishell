/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:05:11 by amandour          #+#    #+#             */
/*   Updated: 2024/09/21 08:54:54 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_plus(char *cmd, char **key, char **value, int *append)
{
	if (ft_strstr(cmd, "+="))
	{
		*value = get_env_value(cmd);
		*key = get_env_key(cmd);
		*append = 1;
	}
	else if (ft_strchr(cmd, '='))
	{
		*key = get_env_key(cmd);
		*value = get_env_value(cmd);
		if (!*key || !*value)
			handle_error(*key, *value);
		*append = 2;
	}
	else
	{
		*key = ft_strdup(cmd);
		*value = ft_strdup("");
		if (!*key || !*value)
			handle_error(*key, *value);
		*append = 3;
	}
}

char	*add_quotes(char *str)
{
	char	*new_str;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new_str = (char *)malloc(len + 3);
	if (!new_str)
		return (NULL);
	new_str[0] = '"';
	ft_strcpy(new_str + 1, str);
	new_str[len + 1] = '"';
	new_str[len + 2] = '\0';
	return (new_str);
}

int	update_or_add(t_env **env, char *key, char *value, int append)
{
	if (is_identifier(key) == -1)
	{
		put_identifier(key, value);
		(free(key), free(value), exit_stat(1));
		return (1);
	}
	if (check_key(*env, key))
	{
		(update_env_value(env, key, value, append), free(key));
		return (exit_stat(0), 1);
	}
	else
	{
		if (ft_strlen(value) == 0 && append == 3)
		{
			if (add_node_env(key, ft_strdup(value), env) == 1)
				(free(key), free(value), exit_stat(0));
		}
		else if (add_node_env(key, add_quotes(value), env) == 1)
			(free(key), free(value), exit_stat(0));
		return (free(value), exit_stat(0), 1);
	}
	return (0);
}

int	process_export_args(t_cmd *cmd, t_env **env)
{
	char	*value;
	char	*key;
	int		append;
	int		i;
	int		valid_cmd;

	i = 1;
	valid_cmd = 0;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == NULL || (!ft_strcmp(cmd->cmd[i], "") && \
			cmd->expd[i] == 2))
		{
			i++;
			continue ;
		}
		append = 0;
		check_plus(cmd->cmd[i], &key, &value, &append);
		if (update_or_add(env, key, value, append) == 1)
			valid_cmd = 1;
		i++;
	}
	return (valid_cmd);
}

void	ft_export(t_cmd *cmd, t_env **env)
{
	t_cmd	*tmp;
	int		valid_cmd;

	tmp = cmd;
	if (ft_strcmp(tmp->cmd[0], "export") != 0)
		return ;
	valid_cmd = process_export_args(tmp, env);
	if (valid_cmd == 0)
		(display_env(*env), exit_stat(0));
}
