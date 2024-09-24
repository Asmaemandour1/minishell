/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otils_expand_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:52:05 by amandour          #+#    #+#             */
/*   Updated: 2024/09/20 23:17:24 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	return (0);
}

char	*ft_strchr(char *s, int c)
{
	char	*chr;

	chr = (char *)s;
	while (*chr != c)
	{
		if (!*chr)
			return (NULL);
		chr++;
	}
	return (chr);
}

char	*ft_strcpy(char *d, char *s1)
{
	int	i;

	i = 0;
	while (*(s1 + i))
	{
		*(d + i) = *(s1 + i);
		i++;
	}
	d[i] = '\0';
	return (d);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0 ;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if ((int)count < 0 || (int)size < 0)
		return (NULL);
	p = (void *)malloc(count * size);
	if (!p)
		return (0);
	ft_bzero(p, count * size);
	return (p);
}
