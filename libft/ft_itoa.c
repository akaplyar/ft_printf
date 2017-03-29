/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 19:13:33 by akaplyar          #+#    #+#             */
/*   Updated: 2016/12/01 20:46:06 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static size_t	get_len(int x)
{
	size_t		i;

	i = 0;
	x = (x < 0 ? x * -1 : x);
	while (x)
	{
		x /= 10;
		i++;
	}
	return (i);
}

static void		ft_swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void		reverse(char *str, size_t len)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = len - 1;
	while (start < end)
	{
		ft_swap(str + start, str + end);
		start++;
		end--;
	}
}

static char		*parse_str(int n, size_t *sign)
{
	char		*str;
	size_t		i;

	i = 0;
	str = (char*)malloc(get_len(n) + sign[0] + sign[1] + 1);
	if (!str)
		return (0);
	if (sign[1])
		str[i++] = '8';
	while (n)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (sign[0])
		str[i++] = '-';
	str[i] = '\0';
	reverse(str, i);
	return (str);
}

char			*ft_itoa(int n)
{
	char	*str;
	size_t	sign[2];

	sign[0] = 0;
	sign[1] = 0;
	if (n == 0)
	{
		str = (char*)malloc(2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (n < 0)
	{
		if (n == -2147483648)
		{
			sign[1] = 1;
			n = -214748364;
		}
		n = -n;
		sign[0] = 1;
	}
	return (parse_str(n, sign));
}
