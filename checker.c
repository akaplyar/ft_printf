#include "ft_printf.h"

int			check_type(t_form *form)
{
	int 	a;
	int		i;

	i = form->type;
	if (!(a = (i == d ? 1 : 0)))
		if (!(a = (i == o || i == O || i == x || i == X) ? 2 : 0))
			if (!(a = (i == b || i == u || i == U) ? 2 : 0))
				if (!(a = (i == c || i == C || i == s || i == S) ? 3 : 0))
					if (!(a = (i == n ? 4 : 0)))
						a = (i == p ? 5 : 0);
	if (i < 0 && *form->out)
		a = 3;
	return (a);
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

void		parse_pointer(t_form *form, va_list argc, char **str)
{
	int		*ptr;

	(void)form;
	ptr = va_arg(argc, int*);
	if (!ptr)
		return ;
	*ptr = (int)(ft_strlen(*str) + g_kostyl);
}