/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otuls_expand_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 03:29:03 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/11 22:58:32 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_identifier(char *key, char *value)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(key, 2);
	if (ft_strcmp(value, ""))
	{
		ft_putstr_fd("=", 2);
		ft_putstr_fd(value, 2);
	}
	ft_putstr_fd("': not a valid identifier\n", 2);
}

long int	mod(long int nbr)
{
	long int	res;

	res = nbr % 256;
	if (res < 0)
		res += 256;
	return (res);
}

size_t	compte_arg(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	is_last_command_exit(t_cmd *cmd_list)
{
	t_cmd	*current;

	if (!cmd_list)
		return (0);
	current = cmd_list;
	while (current->next != NULL)
		current = current->next;
	if (ft_strcmp(current->cmd[0], "exit") == 0)
		return (1);
	return (0);
}
