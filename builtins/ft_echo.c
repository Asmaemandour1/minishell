/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandour <amandour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:17:30 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/11 16:55:41 by amandour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_n_option(t_cmd *cmd, int *i, int *r_line)
{
	int		j;

	while (cmd->cmd[*i])
	{
		if (ft_strncmp(cmd->cmd[*i], "-n", 2) == 0)
		{
			j = 2;
			while (cmd->cmd[*i][j] == 'n')
				j++;
			if (cmd->cmd[*i][j] == '\0')
				*r_line = 1;
			else
				return (*r_line);
			(*i)++;
		}
		else
			return (*r_line);
	}
	return (*r_line);
}

void	ft_echo(t_cmd *cmd, t_env **env)
{
	int		i;
	int		r_line;

	(void)env;
	(1) && (i = 1, r_line = 0);
	r_line = handle_n_option(cmd, &i, &r_line);
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], STDOUT_FILENO);
		if (cmd->cmd[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!r_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	exit_stat(0);
}
