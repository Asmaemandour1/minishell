/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:36:10 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/16 09:48:19 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

void	free_cmd(t_cmd *head)
{
	t_cmd	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head;
		head = head->next;
		ft_free(temp->cmd);
		ft_free(temp->red);
		if (temp->expd)
			free(temp->expd);
		if (temp->fd_herdoc != -1)
			close(temp->fd_herdoc);
		free(temp);
		temp = NULL;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	tmp = NULL;
}

void	t_quotes(char c, int *s_quote, int *d_quote)
{
	if (c == '\'' && !(*d_quote))
		*s_quote = !(*s_quote);
	else if (c == '"' && !(*s_quote))
		*d_quote = !(*d_quote);
}

int	check_pipes(char *str)
{
	int	i;
	int	count_p;
	int	s_quote;
	int	d_quote;

	(1) && (s_quote = 0, d_quote = 0, i = 0);
	while (str[i])
	{
		t_quotes(str[i], &s_quote, &d_quote);
		if (str[i] == '|' && !s_quote && !d_quote)
		{
			count_p = 0;
			while (str[i] == '|')
			{
				while (is_espace(str[i + 1]))
					i++;
				(1) && (count_p++, i++);
			}
			if (count_p > 1)
				return (-1);
			continue ;
		}
		i++;
	}
	return (1);
}
