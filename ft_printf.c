#include "ft_printf.h"

static char			*make_line(char *format, char **str)
{
	size_t		len;
	char		*line;
	char		*ptr;

	ptr = *str;
	len = 0;
	while (*(format + len) && *(format + len) != '%')
		len++;
	line = ft_strsub(format, 0, len);
	*str = ft_strjoin(ptr, line);
	free(line);
	return (format + len);
}

static void			form_init(t_form *form)
{
	form->dl = 0;
	form->cl = 0;
	form->hash = 0;
	form->zero = 0;
	form->plus = 0;
	form->minus = 0;
	form->space = 0;
	form->quote = 0;
	form->dolla = 0;
	form->width = 0;
	form->kostyl = 0;
	form->press = -1;
	form->len = -1;
	form->type = -1;
	form->sign = 0;
	form->out = NULL;
}

static const char	*parse_format(const char *format, va_list argc, va_list tmp, char **str)
{
	t_form			form;
	int				type;

	if (*format == '%')
	{
		form_init(&form);
		format = parse_percent((char*)format, argc, tmp, &form);
		type = check_type(&form);
		if (type == 1 || type == 2)
			parse_int(&form, tmp, str, type);
		else if (type == 3)
			parse_str(&form, tmp, str);
		else if (type == 4)
			parse_pointer(&form , tmp, str);
		else if (type == 5)
			print_memory(&form, tmp, str);
	}
	else
		format = make_line((char *)format, str);
	return (format);
}

int					ft_printf(const char *format, ...)
{
	va_list			argc;
	va_list			tmp;
	size_t			help;
	char			*str;

	if (!format)
		return (0);
	g_kostyl = 0;
	str = (char*)ft_memalloc(1);
	va_start(argc, format);
	va_copy(tmp ,argc);
	while (*format)
		if (!(format = parse_format(format, argc, tmp, &str)))
			return (0);
	va_end(tmp);
	va_end(argc);
	help = ft_strlen(str);
	write(1, str, help);
	return ((int)(help + g_kostyl));
}