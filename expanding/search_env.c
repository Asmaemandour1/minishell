/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:39:01 by amandour          #+#    #+#             */
/*   Updated: 2024/09/17 04:23:26 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var_value(char **cmd, t_env *env)
{
	char	*var_name;
	char	*var_value;
	int		i;

	i = 0;
	if (**cmd == '\0' || **cmd == '$' || **cmd == ' ')
		return (ft_strdup("$"));
	while ((*cmd)[i] && (ft_isalnum((*cmd)[i]) || (*cmd)[i] == '_'))
		i++;
	var_name = ft_substr(*cmd, 0, i);
	if (!var_name)
		return (NULL);
	var_value = get_env_1(var_name, env);
	free(var_name);
	*cmd += i;
	if (var_value)
		return (var_value = ft_strdup(var_value));
	else
		return (ft_strdup(""));
}

char	*append_result(char *result, int *res_len, char *value)
{
	int	value_len;

	if (value)
	{
		value_len = ft_strlen(value);
		result = ft_realloc(result, *res_len,*res_len + value_len + 1);
		if (!result)
			return (NULL);
		ft_memcpy(result + *res_len, value, value_len);
		*res_len += value_len;
	}
	return (result);
}

char	*get_value(char *cmd, char *value, char *result, int *res_len)
{
	if (value)
	{
		result = append_result(result, res_len, value);
		if (*cmd == '?')
			free(value);
	}
	return (result);
}

char	*value_apre_dollar_(char **cmd, t_env *env, int *res_len, char *result)
{
	char	*value;

	(*cmd)++;
	if (**cmd == '?')
	{
		value = ft_itoa(exit_stat(-1));
		(*cmd)++;
	}
	else
	{
		value = get_var_value(cmd, env);
	}
	result = get_value(*cmd, value, result, res_len);
	free(value);
	return (result);
}

char	*search_and_replace_env_var(char *cmd, t_env *env)
{
	char	*dollar_pos;
	char	*result;
	int		premier_len;
	int		res_len;

	(1) && (dollar_pos = ft_strchr(cmd, '$'), result = NULL, res_len = 0);
	while (dollar_pos)
	{
		if (is_single_quotes(cmd, dollar_pos))
		{
			dollar_pos = ft_strchr(dollar_pos + 1, '$');
			continue ;
		}
		premier_len = dollar_pos - cmd;
		result = copie_avant_d(result, &res_len, cmd, premier_len);
		cmd = dollar_pos;
		if (*(cmd + 1) == '\0' || *(cmd + 1) == ' ' || *(cmd + 1) == '"')
			(1) && (result = append_result(result, &res_len, "$"), cmd++);
		else
			result = value_apre_dollar_(&cmd, env, &res_len, result);
		dollar_pos = ft_strchr(cmd, '$');
	}
	return (rest_cmd(result, res_len, cmd));
}
