#include "ft_printf.h"

int			check_type(int i)
{
	int 	a;


	if (!(a = (i == d ? 1 : 0)))
		if (!(a = (i == o || i == O || i == x || i == X) ? 2 : 0))
			if (!(a = (i == b || i == p || i == u || i == U) ? 2 : 0))
				if (!(a = (i == c || i == C || i == s || i == S) ? 3 : 0))
						a = (i == n ? 4 : 0);
	if (i < 0)
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