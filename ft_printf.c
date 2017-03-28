#include "ft_printf.h"

static char			*make_line(char *format, char **str)
{
	size_t		len;
	char		*line;
	char		*ptr;
	int			i;

	ptr = *str;
	i = (*format == '%') ? 1 : 0;
	len = i ? 1 : 0;
	while (*(format + len) && *(format + len) != '%')
		len++;
	line = ft_strsub(format, 0, len);
	*str = ft_strjoin(ptr, line);
	format += (i ? 2 : len);
	free(line);
	return (format);
}

static void			form_init(t_form *form)
{
	form->dl = 0;
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
	form->arg = NULL;
	form->out = NULL;
}

char		*find_type(char *format, va_list argc, t_form *form, int *dolla)
{
	if (*format == 'd' || *format == 'D' || *format == 'i')
		form->type = d;
	else if (*format == 'o' || *format == 'O')
		form->type = (*format == 'o' ? o : O);
	else if (*format == 'u' || *format == 'U')
		form->type = (*format == 'u' ? u : U);
	else if (*format == 'x' || *format == 'X')
		form->type = (*format == 'x' ? x : X);
	else if (*format == 'c' || *format == 'C')
		form->type = (*format == 'c' ? c : C);
	else if (*format == 's' || *format == 'S')
		form->type = (*format == 's' ? s : S);
	else if (*format == 'b' || *format == 'n')
		form->type = (*format == 'b' ? b : n);
	else if (*format == 'p')
	{
		form->hash = 1;
		form->type = p;
	}
	form->arg = va_arg(argc, void *);
	return (format + 1);
}

static const char	*parse_format(const char *format, va_list argc, char **str, int *dolla)
{
	t_form			form;
	int				type;

	if (*format == '%' && *(format + 1) != '%')
	{
		form_init(&form);
		format = parse_percent((char*)format, argc, &form, dolla);
		type = check_type('\0', form.type);
		if (type == 1 || type == 2)
			parse_int(&form, str, dolla, type);
//		else if (type == 3)
//			parse_str(form, str, i, type);
//		else if (type == 4)
//			parse_pointer(form , str, i, type);
	}
	else
		format = make_line((char *)format, str);
	return (format);
}

int					ft_printf(const char *format, ...)
{
	va_list argc;
	char	*str;
	int		dolla[3];

	str = (char*)ft_memalloc(1);
	dolla[0] = check_dolla((char*)format);
	va_start(argc, format);
	while (*format)
		if (!(format = parse_format(format, argc, &str, dolla)))
			return (0);
	va_end(argc);
	dolla[2] = (int)ft_strlen(str);
	write(1, str, (size_t)dolla[2]);
	return (dolla[2]);
}