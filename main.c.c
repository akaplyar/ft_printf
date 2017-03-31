#include "ft_printf.h"
#include <fcntl.h>

int 	main()
{
	int a;
	int fd;

	ft_printf("%'d\n", 123456789);
	a = ft_strcmp("*Kashim a � histoires à raconterIl fait au moins ��c		ly est fantastique!",
				  "*Kashim a � histoires à raconterIl fait au moins ��c		ly est fantastique!");
	ft_printf("%d", a);
	return (0);
}
