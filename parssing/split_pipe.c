/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:22:07 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/08 05:57:58 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	nbr_cmd(char **args)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	if (ft_strcmp(args[i], "|") == 0)
		i++;
	while (args[i] != NULL && ft_strcmp(args[i], "|") != 0)
	{
		if (is_reds(args[i]))
			i += 2;
		else
		{
			c++;
			i++;
		}
	}
	return (c);
}

static	int	nbr_re(char **args)
{
	int	i;
	int	r;

	r = 0;
	i = 0;
	if (ft_strcmp(args[i], "|") == 0)
		i++;
	while (args[i] != NULL && ft_strcmp(args[i], "|") != 0)
	{
		if (!is_reds(args[i]))
			i++;
		else
		{
			r += 2;
			i += 2;
		}
	}
	return (r);
}

static void	add_node(t_cmd **head, t_cmd *node)
{
	t_cmd	*temp;

	if (!node)
		return ;
	if (!(*head))
		*head = node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}

t_cmd	*create_node(char **args, int *i)
{
	t_cmd	*node;
	int		c;
	int		r;
	int		num_cmds;
	int		num_reds;

	(1) && (num_cmds = nbr_cmd(args + (*i)), num_reds = nbr_re(args + (*i)));
	(1) && (c = 0, r = 0);
	node = new_cmd(num_cmds, num_reds);
	if (!node)
		return (NULL);
	while (args[(*i)] && ft_strcmp(args[(*i)], "|") != 0)
	{
		if (is_reds(args[(*i)]))
		{
			node->red[r++] = ft_strdup((args[(*i)++]));
			if (args[(*i)])
				node->red[r++] = ft_strdup((args[(*i)]));
		}
		else
			node->cmd[c++] = ft_strdup((args[(*i)]));
		(*i)++;
	}
	return (node);
}

t_cmd	*fill_nodes(char **args)
{
	t_cmd	*head;
	t_cmd	*node;
	int		i;

	head = NULL;
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
		{
			i++;
			continue ;
		}
		node = create_node(args, &i);
		if (!node)
		{
			free_cmd(head);
			return (NULL);
		}
		add_node(&head, node);
	}
	return (head);
}
