#include "ft_printf.h"

int 	main()
{
	int a;

	a = ft_printf("%#o\n", 0);
	ft_printf("%d\n", a);
	a = printf("%#o\n", 0);
	printf("%d\n", a);
	return (0);
}