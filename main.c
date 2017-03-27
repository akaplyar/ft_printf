#include "ft_printf.h"

int			main(void)
{
	int		a;

	a = 12345;
	ft_printf("%d\n", a);
	printf("lib - %d\n", a);
	return (0);
}