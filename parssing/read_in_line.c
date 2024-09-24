/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_in_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:53:07 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/17 04:11:30 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*process_input(char *input)
{
	char	*trimmed_input;

	trimmed_input = trim_espace(input);
	free (input);
	input = trimmed_input;
	add_history(input);
	if (ft_parsing(input) == -1)
	{
		free(input);
		ft_putstr_fd(" minishell: syntax Error\n", 2);
		exit_stat(258);
		return (NULL);
	}
	return (add_espace(input));
}

char	*handle_readline(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell~$ ");
		if (input == NULL )
		{
			ft_putstr_fd("exit\n", 2);
			exit(0);
		}
		if (!input[0])
		{
			free(input);
			continue ;
		}
		input = process_input(input);
		if (input != NULL)
			return (input);
	}
	return (NULL);
}

char	*read_in_line(void)
{
	return (handle_readline());
}
