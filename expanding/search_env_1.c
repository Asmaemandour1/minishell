/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:42:04 by amandour          #+#    #+#             */
/*   Updated: 2024/09/21 08:51:13 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_strlen(char *str)
{
	if (str)
		return (ft_strlen(str));
	return (0);
}

int	count_elements(char **str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (str[count] != NULL)
	{
		count++;
	}
	return (count);
}

char	*copie_avant_d(char *result, int *res_len, char *cmd, int premier_len)
{
	result = ft_realloc(result,*res_len, *res_len + premier_len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result + *res_len, cmd, premier_len);
	*res_len += premier_len;
	return (result);
}

char	*get_env_1(char *name, t_env *my_env)
{
	while (my_env)
	{
		if (ft_strcmp(my_env->key, name) == 0)
			return (my_env->value);
		my_env = my_env->next;
	}
	return (NULL);
}

char	*rest_cmd(char *result, int res_len, char *cmd)
{
	int	len_fin;

	len_fin = ft_strlen(cmd);
	result = ft_realloc(result, res_len, res_len + len_fin + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result + res_len, cmd, len_fin + 1);
	return (result);
}
