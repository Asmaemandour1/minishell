/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:43:07 by amandour          #+#    #+#             */
/*   Updated: 2024/09/21 06:54:10 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipes(int pipefds[][2], int n)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		if (pipe(pipefds[i]) == -1)
		{
			perror("pipe");
			break ;
		}
		i++;
	}
}

void	close_pipes(int pipefds[][2], int n)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		close(pipefds[i][0]);
		close(pipefds[i][1]);
		i++;
	}
}

void	init_info(t_info *info, t_shell *shell)
{
	info->pids = NULL;
	info->cmd = shell->head;
	info->shell = shell;
	info->saved_stdin = dup(STDIN_FILENO);
	info->saved_stdout = dup(STDOUT_FILENO);
	info->n = cmd_size(info->cmd);
	if (info->n > 1)
		info->pipefd = (int (*)[2])malloc(sizeof(int [2]) * (info->n - 1));
	else
		info->pipefd = NULL;
	empty_args(info);
}

void	execute_processes(t_info *info)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < info->n)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork: ");
			break ;
		}
		if (pid == 0)
		{
			child_process(info, i);
		}
		info->pids[i] = pid;
		info->cmd = info->cmd->next;
	}
	close_pipes(info->pipefd, info->n);
	wait_pro(info);
}

void	execution(t_shell *shell)
{
	t_info	info;

	init_info(&info, shell);
	if (info.n == 1 && check_builtin(info.cmd->cmd[0]))
	{
		builtin(&info);
	}
	else
	{
		create_pipes(info.pipefd, info.n);
		info.pids = malloc(sizeof(int) * info.n);
		if (!info.pids)
		{
			free(info.pipefd);
			free_cmd(shell->head);
			ft_free(shell->args);
			return ;
		}
		execute_processes(&info);
	}
	free(info.pipefd);
	free(info.pids);
}
