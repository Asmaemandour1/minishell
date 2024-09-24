/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcart.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 04:24:42 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/21 09:41:40 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	proc_env_var(char **str, t_env *env, int *expand)
{
	char	*value;

	if (compare_pos1(*str) && !check_quotes1(*str))
		*expand = 1;
	value = search_and_replace_env_var(*str, env);
	if (value == NULL)
		return ;
	if (ft_strcmp(value, "") == 0)
	{
		free(*str);
		*str = ft_strdup("");
		*expand = 2;
	}
	else
	{
		free(*str);
		*str = ft_strdup(value);
	}
	free(value);
}

char	**get_wildcard_results(char *wildcard, int *t_count)
{
	char	*wild_str;
	char	**wildcard_result;

	wild_str = ft_wildcard(wildcard);
	*t_count = 0;
	if (wild_str)
	{
		wildcard_result = splite(wild_str, ' ');
		if (wildcard_result)
		{
			while (wildcard_result[*t_count])
				(*t_count)++;
		}
		free(wild_str);
		return (wildcard_result);
	}
	return (NULL);
}

void	insert_resul(t_cmd *cmd, char **wildcard_res, int *index, int t_count)
{
	int	j;
	int	k;

	if (cmd->cmd[*index])
		(free(cmd->cmd[*index]), cmd->cmd[*index] = NULL);
	cmd->cmd = ft_realloc(cmd->cmd, sizeof(char *) * \
		cmd->cmd_count, sizeof(char *) * (cmd->cmd_count + t_count));
	if (!cmd->cmd)
		(perror("Failed to memory"), exit(EXIT_FAILURE));
	(1) && (k = cmd->cmd_count - 1, j = 0);
	while (k > *index)
	{
		cmd->cmd[k + t_count - 1] = cmd->cmd[k];
		k--;
	}
	while (wildcard_res[j])
	{
		cmd->cmd[*index + j] = ft_strdup(wildcard_res[j]);
		j++;
	}
	cmd->cmd[cmd->cmd_count + t_count - 1] = NULL;
	cmd->cmd_count += (t_count - 1);
	*index += (j - 1);
}
