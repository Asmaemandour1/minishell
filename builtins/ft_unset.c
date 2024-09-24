/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:43:56 by amandour          #+#    #+#             */
/*   Updated: 2024/09/21 09:24:05 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_var(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	(1) && (tmp = *env, prev = NULL);
	if (!key || !env)
		return ;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	is_valid_key( char *key)
{
	int	i;

	if (ft_isdigit(key[0]) || key[0] == '\"')
		return (1);
	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static void	unset_error(char *arg)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static void	process_unset(t_env **env, t_cmd *cmd, int *status)
{
	int	i;

	i = 1;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == NULL || (!ft_strcmp(cmd->cmd[i], "") && \
			cmd->expd[i] == 2))
		{
			i++;
			continue ;
		}
		else if (is_identifier(cmd->cmd[i]) == -1)
		{
			unset_error(cmd->cmd[i]);
			*status = 1;
			i++;
			continue ;
		}
		else if (check_key(*env, cmd->cmd[i]))
			unset_var(env, cmd->cmd[i]);
		i++;
	}
}

void	ft_unset(t_cmd *head, t_env **env)
{
	int	status;

	status = 0;
	if (head->cmd[1] == NULL)
		status = 0;
	else
		process_unset(env, head, &status);
	exit_stat(status);
}
