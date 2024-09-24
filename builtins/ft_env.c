/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:57:42 by amandour          #+#    #+#             */
/*   Updated: 2024/09/18 17:40:35 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env *list)
{
	char	*tmp;

	while (list)
	{
		tmp = remove_q(list->value);
		if (list->key && list->value && list->value[0] != '\0')
			printf("%s=%s\n", list->key, (list->value));
		free(tmp);
		list = list->next;
	}
	exit_stat(0);
}
