/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_q_all_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:38:56 by amandour          #+#    #+#             */
/*   Updated: 2024/09/16 13:45:50 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memmove(void *d1, const void *s1, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	i = 0;
	s = (char *)s1;
	d = (char *)d1;
	if (!d1 && !s1)
		return (NULL);
	if (s == d)
		return (d);
	if (d > s)
	{
		while (len--)
			d[len] = s[len];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (d1);
}

int	check_quotes1(char *str)
{
	int	count;
	int	count1;
	int	s_quotes;
	int	d_quotes;

	(1) && (count = 0, count1 = 0);
	(1) && (s_quotes = 0, d_quotes = 0);
	if (str == NULL)
		return (0);
	while (*str == '"' || *str == '\'' )
	{
		if (*str == '\'' && !d_quotes)
		{
			s_quotes = !s_quotes;
			(1) && (count1++, str++);
		}
		else if (*str == '"' && !s_quotes)
		{
			d_quotes = !d_quotes;
			(1) && (count++, str++);
		}
		else
			str++;
	}
	return (count % 2 || count1 % 2);
}

static void	remove_q_cmd(t_cmd *cmd, int i)
{
	char	*temp;

	temp = remove_q(cmd->cmd[i]);
	if (temp)
		free(cmd->cmd[i]);
	cmd->cmd[i] = temp;
}

static void	remove_q_red(t_cmd *cmd, int i)
{
	char	*temp;

	temp = remove_q(cmd->red[i]);
	if (temp)
	{
		free(cmd->red[i]);
		cmd->red[i] = temp;
	}
}

void	remove_q_all_cmd(t_cmd *cmd)
{
	t_cmd	*current_cmd;
	int		i;

	if (!cmd)
		return ;
	current_cmd = cmd;
	while (current_cmd)
	{
		i = 0;
		while (current_cmd->cmd[i])
		{
			remove_q_cmd(current_cmd, i);
			i++;
		}
		i = 0;
		while (current_cmd->red && current_cmd->red[i])
		{
			if (ft_strcmp(current_cmd->red[i], "<<") == 0)
				i++;
			else
				remove_q_red(current_cmd, i);
			i++;
		}
		current_cmd = current_cmd->next;
	}
}
