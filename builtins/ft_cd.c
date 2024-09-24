/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:03:54 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/20 23:03:22 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_(char *name, t_env *my_env)
{
	while (my_env)
	{
		if (ft_strcmp(my_env->key, name) == 0)
			return (my_env->value);
		my_env = my_env->next;
	}
	return (NULL);
}

static char	*set_path(t_cmd *cmd, char **path, t_env **env)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (!tmp->cmd[1] || ft_strcmp(tmp->cmd[1], "~") == 0 || \
		(!ft_strcmp(cmd->cmd[1], "") && cmd->expd[1] == 2))
	{
		*path = get_env_("HOME", *env);
		if (!*path)
			printf("minishell: cd: HOME not set\n");
	}
	else if (ft_strcmp(tmp->cmd[1], "-") == 0)
	{
		*path = get_env_("OLDPWD", *env);
		if (*path)
			printf("%s\n", *path);
		else
			printf("OLDPWD unset\n");
	}
	else
		*path = tmp->cmd[1];
	return (*path);
}

int	get_dirs(t_env **env, char **path, char **current_dir)
{
	char	*new_pwd;

	new_pwd = NULL;
	if (chdir(*path) != 0)
	{
		perror("cd");
		if (*current_dir)
			free(*current_dir);
		return (exit_stat(1), -1);
	}
	if (current_dir)
		update_cd_add(env, ft_strdup("OLDPWD"), *current_dir, 2);
	new_pwd = getcwd(NULL, 0);
	update_cd_add(env, ft_strdup("PWD"), new_pwd, 2);
	return (exit_stat(0), 0);
}

int	ft_cd(t_cmd *cmd_list, t_env **env)
{
	t_cmd	*cmd;
	char	*current_dir;
	char	*path;

	(1) && (cmd = cmd_list, current_dir = NULL, path = NULL);
	while (cmd)
	{
		if (cmd->cmd && ft_strcmp(cmd->cmd[0], "cd") == 0)
		{
			path = set_path(cmd, &path, env);
			current_dir = getcwd(NULL, 0);
			if (current_dir == NULL)
				ft_putstr_fd("cd: ..: No such file or directory\n", 2);
			if (get_dirs(env, &path, &current_dir) == -1)
				return (-1);
		}
		cmd = cmd->next;
	}
	return (exit_stat(0), -1);
}
