/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_herd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:39:17 by amandour          #+#    #+#             */
/*   Updated: 2024/09/21 06:43:14 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*generate_unique_filename(void)
{
	static size_t	counter;
	char			*filename;
	size_t			tmp;

	counter = 0;
	filename = NULL;
	tmp = 0;
	while (tmp < 1000)
	{
		filename = ft_itoa(counter++);
		if (access(filename, F_OK) != 0)
			return (filename);
		free (filename);
		tmp++;
	}
	return (NULL);
}

void	write_fd(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	handle_signal_herdoc(int signum)
{
	if (signum == SIGINT)
	{
		g_heredoc_flag = 1;
		close (0);
		exit_stat(0);
		return ;
	}
}

int	s_del(char *delimiter)
{
	int	len;

	len = ft_strlen(delimiter);
	if (len >= 2 && delimiter[0] == '\'' && delimiter[len - 1] == '\'')
		return (1);
	return (0);
}

int	d_del(char *delimiter)
{
	int	len;

	len = ft_strlen(delimiter);
	if (len >= 2 && delimiter[0] == '"' && delimiter[len - 1] == '"')
		return (1);
	else
		return (0);
}
