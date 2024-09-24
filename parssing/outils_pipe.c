/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 00:47:22 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/16 11:44:30 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_reds(char *c)
{
	if (!c)
		return (0);
	if (ft_strcmp(c, ">") == 0 || ft_strcmp(c, "<") == 0
		|| ft_strcmp(c, ">>") == 0 || ft_strcmp(c, "<<") == 0)
		return (1);
	return (0);
}

t_cmd	*new_cmd(int num_cmds, int num_reds)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->cmd = (char **)malloc(sizeof(char *) * (num_cmds + 1));
	if (!node->cmd)
		return (free(node), NULL);
	node->cmd[num_cmds] = NULL;
	node->red = (char **)malloc(sizeof(char *) * (num_reds + 1));
	if (!node->red)
		return (free(node->cmd), free(node), NULL);
	node->red[num_reds] = NULL;
	node->next = NULL;
	node->fd_herdoc = -1;
	node->ambiguous_redirect = 0;
	return (node);
}

char	*ft_strdup(char *src)
{
	char	*char_new;
	int		i;

	if (!src)
		return (NULL);
	char_new = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!char_new)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		char_new[i] = src[i];
		i++;
	}
	char_new[i] = '\0';
	return (char_new);
}

int	count_w_test(char *str)
{
	int	s_quote;
	int	d_quote;
	int	cpt;
	int	i;

	(1) && (s_quote = 0, d_quote = 0, cpt = 0, i = 0);
	while (str[i])
	{
		if (str[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (str[i] == '"' && !s_quote)
			d_quote = !d_quote;
		else if (str[i] == ' ' && !s_quote && !d_quote)
			cpt++;
		i++;
		if (str[i] == '\0')
			cpt++;
	}
	return (cpt);
}
