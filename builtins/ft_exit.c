/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:20:43 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/21 09:33:00 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long int	process_digits(const char *nbr, size_t *i)
{
	long int	result;

	result = 0;
	while (nbr[*i])
	{
		if (ft_isdigit(nbr[*i]))
		{
			if (result > (LONG_MAX - (nbr[*i] - '0')) / 10)
				return (-1);
			result = result * 10 + (nbr[*i] - '0');
		}
		else
			return (-1);
		(*i)++;
	}
	return (result);
}

static long int	ft_atoi(char *nb)
{
	long int	result;
	size_t		i;
	int			sign;
	char		*nbr;

	i = 0;
	sign = 1;
	nbr = trim_espace(nb);
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	result = process_digits(nbr, &i);
	if (result == -1 || result == 0)
		return (-1);
	result *= sign;
	if (result > LONG_MAX || result < LONG_MIN)
		return (free(nbr), -1);
	free(nbr);
	return (mod(result));
}

void	put_exit(char *mini, char *path, char *err)
{
	ft_putstr_fd(mini, 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(err, 2);
	exit_st(255);
}

int	check_exit_args(t_cmd *cmd, long int *num)
{
	size_t	nbr_arg;

	nbr_arg = compte_arg(cmd->cmd);
	if (nbr_arg >= 2)
	{
		*num = ft_atoi(cmd->cmd[1]);
	}
	else
	{
		*num = exit_stat(-1);
	}
	if (nbr_arg > 2 && *num != -1)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		exit_stat(1);
		return (1);
	}
	else if (*num == -1)
	{
		write(1, "exit\n", 5);
		put_exit("mini:exit :", cmd->cmd[1], ":numeric argument required\n");
		return (1);
	}
	return (0);
}

void	ft_exit(t_cmd *cmd)
{
	t_cmd		*tmp;
	long int	num;
	int			is_piped;

	tmp = cmd;
	num = 1;
	is_piped = 0;
	if (is_last_command_exit(tmp))
	{
		if (tmp->next)
			is_piped = 1;
		while (tmp->next)
			tmp = tmp->next;
		if (check_exit_args(tmp, &num))
			return ;
		if (!is_piped)
			write(1, "exit\n", 5);
		(exit_stat(num), exit(num));
	}
}
