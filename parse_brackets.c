/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_brackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 03:02:25 by akaplyar          #+#    #+#             */
/*   Updated: 2017/03/31 03:02:26 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*parse_color2(char *format)
{
	if (!ft_strncmp(format, "{blue}", 6))
	{
		ft_putstr("\x1B[34m\0");
		return (format + 6);
	}
	else if (!ft_strncmp(format, "{magenta}", 9))
	{
		ft_putstr("\x1B[35m\0");
		return (format + 9);
	}
	else if (!ft_strncmp(format, "{cyan}", 6))
	{
		ft_putstr("\x1B[36m\0");
		return (format + 6);
	}
	else if (!ft_strncmp(format, "{white}", 7))
	{
		ft_putstr("\x1B[37m\0");
		return (format + 7);
	}
	else
		return (format);
}

static char	*parse_color(char *format)
{
	if (!ft_strncmp(format, "{black}", 7))
	{
		ft_putstr("\x1B[30m\0");
		return (format + 7);
	}
	if (!ft_strncmp(format, "{red}", 5))
	{
		ft_putstr("\x1B[31m\0");
		return (format + 5);
	}
	else if (!ft_strncmp(format, "{green}", 7))
	{
		ft_putstr("\x1B[32m\0");
		return (format + 7);
	}
	else if (!ft_strncmp(format, "{yellow}", 9))
	{
		ft_putstr("\x1B[33m\0");
		return (format + 9);
	}
	else
		return (parse_color2(format));
}

char		*parse_brackets(char *format, t_form *form, va_list argc, int *fd)
{
	if (!ft_strncmp(format, "{fd}", 4))
	{
		form->fd = va_arg(argc, int);
		if (form->fd < 2 || (write(form->fd, 0, 0) < 0))
			form->fd = 1;
		*fd = form->fd;
		return (format + 4);
	}
	else if (!ft_strncmp(format, "{eofd}", 6))
	{
		form->fd = 1;
		*fd = 1;
		return (format + 6);
	}
	else if (!ft_strncmp(format, "{eoc}", 5))
	{
		ft_putstr("\x1B[0m\0");
		return (format + 5);
	}
	else
		format = parse_color(format);
	return (format);
}
