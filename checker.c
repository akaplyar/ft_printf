#include "ft_printf.h"

int			check_dolla(char *format, t_form *form)
{
	int		a;
	int		i;

	a = -1;
	i = 0;
	if (format[i] == '*')
		format++;
	while (format[i] && ft_isdigit(format[i]))
		i++;
	if (format[i] == '$')
	{
		a = ft_atoi(format);
		if (!form->dolla)
			form->dolla = 1;
	}
	return (i ? a : i);
}

int			check_flags(char c)
{
	int		a;

	a = 0;
	a += (c == '#' ? 1 : 0);
	a += (c == ' ' ? 1 : 0);
	a += (c == '+' ? 1 : 0);
	a += (c == '-' ? 1 : 0);
	a += (c == '0' ? 1 : 0);
	a += (c == '\'' ? 1 : 0);
	return (a);
}