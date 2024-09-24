/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:09:33 by amandour          #+#    #+#             */
/*   Updated: 2024/09/20 23:18:19 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_wildcard(t_cmd *cmd, int *index)
{
	char	**wildcard_result;
	int		t_count;

	if (is_wildcard_quoted(cmd->cmd[*index]))
		return ;
	wildcard_result = get_wildcard_results(cmd->cmd[*index], &t_count);
	if (wildcard_result && t_count > 0)
	{
		insert_resul(cmd, wildcard_result, index, t_count);
		ft_free(wildcard_result);
	}
	else
		return ;
}

void	expand_cmd(t_cmd *cmd, t_env *env)
{
	int	i;

	if (cmd->cmd && cmd->expd)
	{
		i = 0;
		while (cmd->cmd[i] && i < cmd->cmd_count)
		{
			if (ft_strchr(cmd->cmd[i], '$'))
			{
				proc_env_var(&cmd->cmd[i], env, &cmd->expd[i]);
				i++;
			}
			else if (ft_strchr(cmd->cmd[i], '*') && \
				!is_wildcard_quoted(cmd->cmd[i]))
			{
				expand_wildcard(cmd, &i);
			}
			else
				i++;
		}
	}
}

void	ambiguous(char *red, t_cmd *cmd)
{
	if (!ft_strcmp(red, "*"))
	{
		ft_putstr_fd(red, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		cmd->ambiguous_redirect = 1;
	}
	else if (ft_count_w(red, ' ') > 1 || !ft_strcmp(red, ""))
	{
		ft_putstr_fd(red, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		cmd->ambiguous_redirect = 1;
	}
}

void	expand_redirections(t_cmd *cmd, t_env *env)
{
	int	i;

	if (cmd->red)
	{
		i = 0;
		while (cmd->red[i])
		{
			if (!ft_strcmp(cmd->red[i], "<<"))
			{
				i += 2;
				continue ;
			}
			ambiguous(cmd->red[i], cmd);
			if (cmd->ambiguous_redirect)
				return ;
			else if (ft_strchr(cmd->red[i], '$'))
			{
				proc_env_var(&cmd->red[i], env, &cmd->expd[cmd->cmd_count + i]);
				ambiguous(cmd->red[i], cmd);
				if (cmd->ambiguous_redirect)
					return ;
			}
			i++;
		}
	}
}

void	expanding(t_shell *shell)
{
	t_cmd	*tmp;
	int		total;

	tmp = shell->head;
	while (tmp)
	{
		tmp->cmd_count = 0;
		while (tmp->cmd && tmp->cmd[tmp->cmd_count])
			tmp->cmd_count++;
		tmp->red_count = 0;
		while (tmp->red && tmp->red[tmp->red_count])
			tmp->red_count++;
		total = tmp->cmd_count + tmp->red_count;
		tmp->expd = ft_calloc(total, sizeof(int));
		if (!tmp->expd)
		{
			ft_putstr_fd("memory allocation en error \n", 2);
			exit(1);
		}
		expand_cmd(tmp, shell->my_env);
		expand_redirections(tmp, shell->my_env);
		tmp = tmp->next;
	}
}
