/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:43:41 by amandour          #+#    #+#             */
/*   Updated: 2024/09/21 08:24:34 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_output_trunc(char **red, int *i)
{
	int	fd;

	fd = open(red[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*i += 2;
	return (1);
}

int	redirect_output_append(char **red, int *i)
{
	int	fd;

	fd = open(red[*i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*i += 2;
	return (1);
}

int	redirect_input(char **red, int *i)
{
	int	fd;

	fd = open(red[*i + 1], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	*i += 2;
	return (1);
}

int	handle_heredoc(int fd_heredoc)
{
	dup2(fd_heredoc, STDIN_FILENO);
	close(fd_heredoc);
	return (1);
}

int	redirections(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->red && cmd->red[i])
	{
		if (cmd->ambiguous_redirect)
			return (0);
		if (ft_strcmp(cmd->red[i], ">") == 0 && cmd->red[i + 1])
			redirect_output_trunc(cmd->red, &i);
		else if (ft_strcmp(cmd->red[i], ">>") == 0 && cmd->red[i + 1])
			redirect_output_append(cmd->red, &i);
		else if (ft_strcmp(cmd->red[i], "<") == 0 && cmd->red[i + 1])
			redirect_input(cmd->red, &i);
		else if (ft_strcmp(cmd->red[i], "<<") == 0 && cmd->red[i + 1])
			(handle_heredoc(cmd->fd_herdoc), i += 2);
		else
			i++;
	}
	return (1);
}
