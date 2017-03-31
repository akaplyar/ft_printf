#include "ft_printf.h"
#include <fcntl.h>

int 	main()
{
	int a;
	int fd;

	fd = open("output", O_WRONLY);
	a = ft_printf("%4$s %1$s{fd}%s{eofd}\n", "dolla", fd, "test", "this is");
	ft_printf("%d\n", a);
	a = printf("%3$s %1$s %s\n", "dolla", "test", "this is");
	printf("%d", a);
	return (0);
}
