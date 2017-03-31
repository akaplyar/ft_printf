/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 03:02:59 by akaplyar          #+#    #+#             */
/*   Updated: 2017/03/31 03:05:14 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		cut_press(t_form *form)
{
	char		*tmp;
	size_t		press;

	if (form->press < 0)
		return ;
	press = (size_t)form->press;
	if (ft_strlen(form->out) <= press)
		return ;
	tmp = form->out;
	form->out = ft_strsub(tmp, 0, press);
	free(tmp);
}

static void		choose_print(t_form *form, char tmp, int *size)
{
	if (tmp == '\n')
		*size += write(form->fd, "\\n", 2);
	else if (tmp == '\t')
		*size += write(form->fd, "\\t", 2);
	else if (tmp == '\v')
		*size += write(form->fd, "\\v", 2);
	else if (tmp == '\f')
		*size += write(form->fd, "\\f", 2);
	else if (tmp == '\r')
		*size += write(form->fd, "\\r", 2);
	else if (tmp > 0 && tmp < 32)
	{
		tmp += 64;
		*size += write(form->fd, "^", 1);
		*size += write(form->fd, &tmp, 1);
	}
	else
		*size += write(form->fd, &tmp, 1);
}

void			print_non_printable(t_form *form, va_list argc, int *size)
{
	char		*ptr;
	char		tmp;

	if ((ptr = va_arg(argc, char*)))
		form->out = ft_strdup(ptr);
	else
	{
		*size += write(1, "(null)", 6);
		return ;
	}
	cut_press(form);
	fill_width(form);
	ptr = form->out;
	while (*form->out)
	{
		tmp = *form->out;
		choose_print(form, tmp, size);
		form->out++;
	}
	free(ptr);
}

static void		get_char(t_form *form, va_list argc, int *size)
{
	char		ctmp;
	char		zero;

	if (form->type == c)
	{
		ctmp = va_arg(argc, int);
		form->out = ft_strsub(&ctmp, 0, 1);
	}
	else
		form->out = ft_strsub(form->out, 0, 1);
	if (form->type == c	&& *form->out < 32 && *form->out > -1)
	{
		zero = *form->out;
		form->nul = 1;
	}
	fill_width(form);
	if (!form->minus)
		*size += write(form->fd, form->out, ft_strlen(form->out));
	if (form->nul)
		*size += write(form->fd, &zero, 1);
	if (form->minus)
		*size += write(form->fd, form->out, ft_strlen(form->out));
	free(form->out);
}

void			parse_str(t_form *form, va_list argc, int *size)
{
	char		*ptr;

	if (form->type == S)
		parse_wstr(form, argc, size);
	else if (form->type == C)
		get_wchar(form, argc, size);
	else if (form->type == c || form->type < 0)
		get_char(form, argc, size);
	else
	{
		ptr = va_arg(argc, char*);
		if (!ptr)
			form->out = ft_strdup("(null)");
		else
			form->out = ft_strdup(ptr);
		cut_press(form);
		fill_width(form);
		*size += write(form->fd, form->out, ft_strlen(form->out));
		free(form->out);
	}
}
