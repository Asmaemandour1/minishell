/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otils_expand2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:49:55 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/11 22:51:26 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	slen(long n)
{
	if (n == 0)
		return (0);
	else if (n < 0)
		return (1 + slen(n * -1));
	return (1 + slen(n / 10));
}

static	char	*get_str(long n, int s)
{
	char	*str;

	if (n == 0)
		s++;
	str = (char *)malloc((s + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
		*str = '0';
	else if (n < 0)
	{
		*str = '-';
		n *= -1;
	}
	*(str + s--) = '\0';
	while (n > 0)
	{
		*(str + s--) = n % 10 + 48;
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long	m;

	m = n;
	return (get_str(m, slen(m)));
}

size_t	ft_strlcpy(char *d, char *s, size_t l)
{
	size_t	i;

	i = 0;
	if (l != 0)
	{
		while (s[i] != '\0' && i < (l - 1))
		{
			d[i] = s[i];
			i++;
		}
		d[i] = '\0';
	}
	return (ft_strlen(s));
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*niveau;
	size_t	longeur;
	size_t	fin;

	if (!s)
		return (0);
	longeur = ft_strlen(s);
	if (start >= longeur)
		return (ft_strdup(""));
	fin = 0;
	if (longeur >= start)
		fin = longeur - start;
	if (fin > len)
		fin = len;
	niveau = (char *)malloc((fin + 1) * sizeof(char));
	if (!niveau)
		return (0);
	ft_strlcpy(niveau, s + start, fin + 1);
	return (niveau);
}
