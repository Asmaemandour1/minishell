/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_execution_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:42:35 by amandour          #+#    #+#             */
/*   Updated: 2024/09/21 06:53:43 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_redirections(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	builtin(t_info *info)
{
	if (redirections(info->cmd))
	{
		execute_builtin(info->cmd, info->shell);
		reset_redirections(info->saved_stdin, info->saved_stdout);
	}
	else
		reset_redirections(info->saved_stdin, info->saved_stdout);
}

void	child_process(t_info *info, int i)
{
	if (i != 0)
		dup2(info->pipefd[i - 1][0], STDIN_FILENO);
	if (i != info->n - 1)
		dup2(info->pipefd[i][1], STDOUT_FILENO);
	close_pipes(info->pipefd, info->n);
	if (redirections(info->cmd))
	{
		if (check_builtin(info->cmd->cmd[0]))
			execute_builtin(info->cmd, info->shell);
		else
			execute_command(info->cmd, info->shell->my_env);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}

void	exec_command_not_found(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	free(command);
	exit_stat(127);
	exit(127);
}

void	wait_pro(t_info *info)
{
	pid_t	wpid;
	int		i;

	i = 0;
	while (i < info->n)
	{
		wpid = waitpid(info->pids[i], &info->shell->status, 0);
		if (WIFEXITED(info->shell->status))
		{
			exit_stat(WEXITSTATUS(info->shell->status));
		}
		else if (WIFSIGNALED(info->shell->status))
		{
			if (WTERMSIG(info->shell->status) == SIGINT)
				exit_stat(130);
			else if (WTERMSIG(info->shell->status) == SIGQUIT)
				exit_stat(131);
		}
		i++;
	}
	reset_redirections(info->saved_stdin, info->saved_stdout);
}
