/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:34:18 by achahlao          #+#    #+#             */
/*   Updated: 2024/08/06 17:17:19 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes(const char *str)
{
	int	i;
	int	s_quote;
	int	d_quote;

	(1) && (i = 0, s_quote = 0, d_quote = 0);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (str[i] == '"' && !s_quote)
			d_quote = !d_quote;
		i++;
	}
	if (s_quote || d_quote)
		return (-1);
	return (1);
}
