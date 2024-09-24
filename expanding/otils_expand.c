/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:53:44 by amandour          #+#    #+#             */
/*   Updated: 2024/09/11 00:11:29 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (-1);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (-1);
		i++;
	}
	return (1);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = (char *)dest;
	s = (const char *)src;
	while (n--)
	{
		*d++ = *s++;
	}
	return (dest);
}

void	*ft_realloc(void *ptr, size_t cursize, size_t newsize)
{
	char	*newptr;

	if (ptr == NULL)
		return (malloc(newsize));
	if (newsize <= cursize)
		return (ptr);
	newptr = malloc(newsize);
	if (!newptr)
		return (NULL);
	ft_memcpy(newptr, ptr, cursize);
	free(ptr);
	return (newptr);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}
