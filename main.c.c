#include "ft_printf.h"

int 	main()
{
	int a;

	a = ft_printf("%C\n", 0);
	ft_printf("%d\n", a);
	a = printf("%lc\n", 0);
	printf("%d\n", a);
	return (0);
}