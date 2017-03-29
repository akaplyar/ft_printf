#include "ft_printf.h"

int			main(void)
{
	int		a, b;
	wchar_t w = L'\x3b5';

	a = 12345;
	b = a;
	ft_printf("%#-10X|-my-|\n", a);
	printf("%#-10X|-lib|\n", b);
	ft_printf("%S\n", w);
//	printf("%S\n", w);
	return (0);
}