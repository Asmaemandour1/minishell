/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:38:50 by amandour          #+#    #+#             */
/*   Updated: 2024/09/19 09:13:48 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_and_insert(t_cmd *cmd, char ***arr, int *i)
{
	char	**split;
	int		s_count;
	int		curr_size;
	int		j;

	(void)cmd;
	(1) && (split = splite((*arr)[*i], ' '), s_count = 0);
	while (split[s_count])
		s_count++;
	curr_size = 0;
	while ((*arr)[curr_size])
		curr_size++;
	*arr = ft_realloc(*arr, sizeof(char *) * (curr_size + 1),
			sizeof(char *) * (curr_size + s_count - 1 + 1));
	ft_memmove(&(*arr)[*i + s_count], &(*arr)[*i + 1],
		sizeof(char *) * (curr_size - *i));
	(free((*arr)[*i]), j = 0);
	while (j < s_count)
	{
		(*arr)[*i + j] = split[j];
		j++;
	}
	free(split);
	*i += s_count;
	return (s_count - 1);
}

void	realloc_arr(char ***arr, int nev_taille)
{
	int	taille;

	taille = 0;
	while ((*arr)[taille])
		taille++;
	*arr = ft_realloc(*arr, sizeof(char *) * (taille + 1),
			sizeof(char *) * (taille + nev_taille + 1));
}

void	process_cmd_element(t_cmd *cmd, int is_red)
{
	char	***arr;
	int		i;
	int		new_size;

	i = 0;
	new_size = 0;
	if (is_red)
		arr = &cmd->red;
	else
		arr = &cmd->cmd;
	while ((*arr)[i])
	{
		if (ft_strchr((*arr)[i], ' ') && cmd->expd[i])
			new_size += split_and_insert(cmd, arr, &i);
		else
			i++;
	}
	if (new_size > 0)
		realloc_arr(arr, new_size);
}

void	process_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		process_cmd_element(cmd, 0);
		process_cmd_element(cmd, 1);
		cmd = cmd->next;
	}
}
