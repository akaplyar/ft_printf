#include "ft_printf.h"

int			main(void)
{
	int		a, b;

	a = 12345;
	b = a;
	ft_printf("%#-10X|-my-|\n", a);
	printf("%#-10X|-lib|\n", b);
	return (0);
}