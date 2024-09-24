/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:39:14 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/19 08:22:48 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	b_pwd(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (shell->stored_cwd)
		{
			printf ("%s/..\n", shell->stored_cwd);
			exit_stat(0);
		}
		else
			(perror("getcwd"), exit_stat(1));
		return ;
	}
	printf("%s\n", cwd);
	if (shell->stored_cwd)
		free(shell->stored_cwd);
	shell->stored_cwd = ft_strdup(cwd);
	free(cwd);
	exit_stat(0);
}

void	exec_pwd(t_shell *shell, t_cmd *all_cmd)
{
	t_cmd	*cmd;

	cmd = all_cmd;
	while (cmd)
	{
		if (cmd->cmd && ft_strcmp(cmd->cmd[0], "pwd") == 0)
		{
			b_pwd(shell);
			return ;
		}
		cmd = cmd->next;
	}
}
