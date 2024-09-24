/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_execution1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 01:35:19 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/21 08:53:23 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_command_path(char *command, t_env *env)
{
	char	*path;

	if (!command)
		return (NULL);
	if (access(command, X_OK) == 0)
		path = ft_strdup(command);
	else if (command[0] == '/' || ft_strncmp(command, "./", 2) == 0)
		path = ft_strdup(command);
	else
	{
		path = get_path(command, env_to_tab(env));
		if (!path && ft_strchr(command, '/'))
			return (command);
	}
	return (path);
}

void	put_erroor_126(char *mini, char *path, char *err)
{
	ft_putstr_fd(mini, 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(err, 2);
	exit_stat(126);
	exit(126);
}

void	put_erroor_127(char *mini, char *path, char *err)
{
	ft_putstr_fd(mini, 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(err, 2);
	exit_stat(127);
	exit(127);
}

void	execute_path(char *path, t_cmd *cmd, t_env *env)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			put_erroor_126("minishell: ", path, ": Is a directory\n");
		else if (access(path, X_OK) == 0)
		{
			redirections(cmd);
			execve(path, cmd->cmd, env_to_tab(env));
			if (errno == ENOEXEC)
				put_erroor_126("minishell: ", path, ": Exec format error\n");
			perror("execve");
			(exit_stat(126), exit(126));
		}
		else
			put_erroor_126("minishell: ", path, ": Permission denied\n");
	}
	else
	{
		if (errno == ENOENT)
			put_erroor_127("minishell:", path, ": No such file or directory\n");
		else
			put_erroor_127("minishell: ", path, ": Error accessing file\n");
	}
}

void	execute_command(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	*command;

	command = ft_strdup(cmd->cmd[0]);
	if (!command || (command[0] == '\0' && cmd->expd[0] == 2))
		return ;
	if (is_all_spaces(command))
		exec_command_not_found(command);
	path = handle_command_path(command, env);
	if (path)
	{
		execute_path(path, cmd, env);
		if (path != command)
			free(path);
	}
	else
		put_erroor_127("minishell: ", command, ": command not found\n");
	free(command);
	exit(EXIT_FAILURE);
}
