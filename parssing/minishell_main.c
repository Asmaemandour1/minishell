/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:53:22 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/21 10:16:45 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_env(char **env, t_env **new_env)
{
	*new_env = NULL;
	if (ft_get_env(env, new_env) == -1)
		return (-1);
	return (0);
}
