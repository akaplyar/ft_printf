/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 02:49:17 by akaplyar          #+#    #+#             */
/*   Updated: 2017/03/31 02:51:50 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*make_line(char *format, int *size)
{
	size_t		len;
	char		*line;

	len = 0;
	while (*(format + len) && *(format + len) != '%' && *(format + len) != '{')
		len++;
	line = ft_strsub(format, 0, len);
	*size += write(1, line, ft_strlen(line));
	free(line);
	return (format + len);
}

static void	form_init(t_form *form, int *fd)
{
	if (!*fd)
		*fd = 1;
	form->cl = 0;
	form->nul = 0;
	form->fd = *fd;
	form->hash = 0;
	form->zero = 0;
	form->plus = 0;
	form->minus = 0;
	form->space = 0;
	form->quote = 0;
	form->dolla = 0;
	form->width = 0;
	form->press = -1;
	form->len = -1;
	form->type = -1;
	form->sign = 0;
	form->out = NULL;
}

static char	*parse_format(char *format, va_list argc, va_list tmp, int *size)
{
	t_form		form;
	int			type;
	static int	fd;

	if (*format == '%')
	{
		form_init(&form, &fd);
		format = parse_percent((char*)format, argc, tmp, &form);
		type = check_type(&form);
		if (type == 1 || type == 2)
			parse_int(&form, tmp, size, type);
		else if (type == 3)
			parse_str(&form, tmp, size);
		else if (type == 4)
			parse_pointer(&form, tmp, size);
		else if (type == 5)
			print_memory(&form, tmp, size);
		else if (type == 6)
			print_non_printable(&form, tmp, size);
	}
	else if (*format == '{')
		format = parse_brackets((char*)format, &form, tmp, &fd);
	else
		format = make_line((char *)format, size);
	return (format);
}

int			ft_printf(const char *format, ...)
{
	va_list		argc;
	va_list		tmp;
	int			size;

	if (!format)
		return (0);
	size = 0;
	va_start(argc, format);
	va_copy(tmp, argc);
	while (*format)
		if (!(format = parse_format((char *)format, argc, tmp, &size)))
			return (0);
	va_end(tmp);
	va_end(argc);
	return (size);
}
