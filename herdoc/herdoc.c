/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:48:00 by amandour          #+#    #+#             */
/*   Updated: 2024/09/21 11:11:05 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

int	sd_quote(char *delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

static void	handle_heredoc_input(int fd_w, char *delimiter, t_shell *shell)
{
	char	*input_line;
	char	*exp_line;
	char	*tmp;

	tmp = remove_q(delimiter);
	rl_catch_signals = 1;
	signal(SIGINT, handle_signal_herdoc);
	while (1)
	{
		input_line = readline("> ");
		if (!input_line || ft_strcmp(tmp, input_line) == 0)
			break ;
		if (*input_line == '\0')
			write(fd_w, "", 0);
		if (d_del(delimiter) || s_del(delimiter) || sd_quote(delimiter))
			write_fd(fd_w, input_line);
		else
		{
			exp_line = search_and_replace_env_var(input_line, shell->my_env);
			write_fd(fd_w, exp_line);
			free(exp_line);
		}
		free(input_line);
	}
	(free(input_line), free(tmp));
}

static int	open_heredoc(char **filename, char **name_fre, int *fd_w, int *fd_r)
{
	*name_fre = generate_unique_filename();
	*filename = ft_strjoin("/private/tmp/file_", *name_fre);
	free(*name_fre);
	unlink(*filename);
	*fd_w = open(*filename, O_CREAT | O_WRONLY, 0777);
	*fd_r = open(*filename, O_CREAT | O_RDONLY, 0777);
	if (*fd_w == -1 || *fd_r == -1)
		return (-1);
	unlink(*filename);
	return (0);
}

static int	process_redirection(t_cmd *cmd, t_shell *shell, char *del)
{
	char	*filename;
	char	*name_fre;
	int		fd_w;
	int		fd_r;
	int		f;

	(1) && (g_heredoc_flag = 0, f = dup(0));
	if (open_heredoc(&filename, &name_fre, &fd_w, &fd_r) == -1)
		return (-1);
	handle_heredoc_input(fd_w, del, shell);
	rl_catch_signals = 0;
	if (g_heredoc_flag)
	{
		(1) && (g_heredoc_flag = 0, dup2(f, 0));
		(close(f), close(fd_r));
		(close(fd_w), free(filename), exit_stat(1));
		(free_cmd(shell->head), ft_free(shell->args));
		return (free(shell->input), -3);
	}
	(1) && (close(fd_w), close(f));
	free(filename);
	if (cmd->fd_herdoc != -1)
		close(cmd->fd_herdoc);
	cmd->fd_herdoc = fd_r;
	return (0);
}

int	ft_heredoc(t_shell *shell)
{
	t_cmd	*cmd;
	int		i;
	int		check_hec;

	cmd = shell->head;
	while (cmd)
	{
		i = 0;
		while (cmd->red && cmd->red[i])
		{
			if (ft_strcmp(cmd->red[i], "<<") == 0 && cmd->red[i + 1])
			{
				check_hec = process_redirection(cmd, shell, cmd->red[i + 1]);
				if (check_hec == -3)
					return (-3);
				if (check_hec == -1)
					return (-1);
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (1);
}
