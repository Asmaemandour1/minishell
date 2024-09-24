/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_execution_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:04:23 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/21 00:45:30 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(char *cmd)
{
	if (cmd && (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || \
				!ft_strcmp(cmd, "pwd") || \
				!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") || \
				!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit")))
		return (1);
	return (0);
}

void	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		ft_echo(cmd, &(shell->my_env));
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		ft_cd(cmd, &(shell->my_env));
	else if (!ft_strcmp(cmd->cmd[0], "pwd"))
		exec_pwd(shell, cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		ft_export(cmd, &(shell->my_env));
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		ft_unset(cmd, &(shell->my_env));
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		ft_env((shell->my_env));
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		ft_exit(shell->head);
}

int	cmd_size(t_cmd *head)
{
	t_cmd	*tmp;
	int		cpt;

	if (!head)
		return (0);
	(1) && (tmp = head, cpt = 0);
	while (tmp)
	{
		cpt++;
		tmp = tmp->next;
	}
	return (cpt);
}

void	set_st_ext(int exit_st, int N_exit)
{
	exit_stat(exit_st);
	exit(N_exit);
}

int	is_all_spaces(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!is_espace(*str))
			return (0);
		str++;
	}
	return (1);
}
