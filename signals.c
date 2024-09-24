/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:07:54 by amandour          #+#    #+#             */
/*   Updated: 2024/09/21 09:46:52 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	t_info	info;

	if (signum == SIGINT)
	{
		if (!waitpid(-1, &info.shell->status, WNOHANG))
			return ;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_stat(1);
	}
	else if (signum == SIGQUIT)
	{
		(void)signum;
		exit_stat(1);
	}
}
