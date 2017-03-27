#include "ft_printf.h"

char		*find_type(char *format, va_list argc, t_form *form, int *i)
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
	if (*format == 'p')
	{
		form->hash = 1;
		form->type = p;
	}
	form->arg = va_arg(argc, void *);
	return (format + 1);
}

static char	*find_len(char *format, t_form *form)
{
	while (*format && !check_type(*format, -1))
	{
		if (*format == 'l')
			form->len = (*(format + 1) == 'l' ? ll : l);
		else if (*format == 'L')
			form->len = L;
		else if (*format == 'h')
			form->len = (*(format + 1) == 'h' ? hh : h);
		else if (*format == 'j')
			form->len = j;
		else if (*format == 'z')
			form->len = z;
		format++;
	}
	return (format);
}

static char	*find_press(char *format, va_list argc, t_form *form, int *i)
{
	if (*format == '.')
	{
		form->zero = 0;
		format++;
		if (*format == '*')
		{
			form->press = va_arg(argc, int);
			format++;
		}
		else
		{
			form->press = ft_atoi(format);
			while (ft_isdigit(*format))
				format++;
		}
	}
	return (find_len(format, form));
}
static char	*find_width(char *format, va_list argc, t_form *form, int *i)
{
	if (*format == '*')
	{
		form->width = va_arg(argc, int);
		if (form->width < 0)
		{
			form->minus = 1;
			form->width *= -1;
		}
	}
	else if (ft_isdigit(*format))
	{
		form->width = ft_atoi(format);
		while (ft_isdigit(*format))
			format++;
	}
	return (find_press(format, argc, form, i));
}

char		*find_flags(char *format, va_list argc, t_form *form, int *i)
{
	while (*format && check_flags(*format))
	{
		if (*format == '#')
			form->hash = 1;
		else if (*format == '\'')
			form->quote = 1;
		else if (*format == ' ' && !form->plus)
			form->space = 1;
		else if (*format == '0' && !form->minus)
			form->zero = 1;
		else if (*format == '+')
		{
			form->plus = 1;
			form->space = 0;
		}
		else if (*format == '-')
		{
			form->minus = 1;
			form->zero = 0;
		}
		format++;
	}
	return (find_width(format, argc, form, i));
}