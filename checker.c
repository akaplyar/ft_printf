#include "ft_printf.h"

int			check_type(char c, int i)
{
	int 	a;

	if (i < 0)
	{
		if (!(a = (c == 'd' || c == 'i' || c == 'D') ? 1 : 0))
			if (!(a = (c == 'o' || c == 'O' || c == 'x' || c == 'X') ? 2 : 0))
				if (!(a = (c == 'b' || c == 'p') ? 2 : 0))
					if (!(a = (c == 'c' || c == 'C') ? 3 : 0))
						if (!(a = (c == 's' || c == 'S') ? 3 : 0))
							a = (c == 'n' ? 4 : 0);
	}
	else
	{
		if (!(a = (i == d ? 1 : 0)))
			if (!(a = (i == o || i == O || i == x || i == X) ? 2 : 0))
				if (!(a = (i == b || i == p) ? 2 : 0))
					if (!(a = (i == c || i == C) ? 3 : 0))
						if (!(a = (i == s || i == S) ? 3 : 0))
							a = (i == n ? 4 : 0);
	}
	return (a);
}

int			check_dolla(char *format)
{
	char	*ptr;

	while (*format && *format != '%')
		format++;
	if (!*format)
		return (0);
	ptr = format;
	while (*ptr && !check_type(*ptr, -1))
		ptr++;
	if (!*ptr)
		return (-1);
	while (format < ptr)
	{
		if (*format == '$')
			return (1);
		format++;
	}
	return (0);
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