/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:39:32 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/20 16:13:08 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
		return (S_ISDIR(path_stat.st_mode));
	return (0);
}

void	free_fil_args(char **filtered_cmd)
{
	int	i;

	if (!filtered_cmd)
		return ;
	i = 0;
	while (filtered_cmd[i])
	{
		free(filtered_cmd[i]);
		i++;
	}
	free(filtered_cmd);
}

void	empty_args(t_info *info)
{
	t_cmd	*tmp;
	char	**filt_cmd;
	int		i;
	int		j;
	int		count;

	(1) && (i = -1, count = 0, tmp = (info)->cmd);
	while (tmp->cmd[++i])
	{
		if (tmp->cmd[i][0] != '\0' || \
			(tmp->cmd[i][0] == '\0' && tmp->expd[i] != 2))
			count++;
	}
	filt_cmd = malloc((count + 1) * sizeof(char *));
	if (!filt_cmd)
		return ;
	(1) && (j = 0, i = -1);
	while (tmp->cmd[++i])
	{
		if (tmp->cmd[i][0] != '\0' || \
			(tmp->cmd[i][0] == '\0' && tmp->expd[i] != 2))
			filt_cmd[j++] = ft_strdup(tmp->cmd[i]);
	}
	(free_fil_args(tmp->cmd), filt_cmd[j] = NULL);
	(info)->cmd->cmd = filt_cmd;
}
