#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <limits.h>

enum	e_mode
{
	hh,
	h,
	l,
	ll,
	L,
	j,
	z,
	t,
	d,
	o,
	O,
	u,
	U,
	x,
	X,
	c,
	C,
	s,
	S,
	p,
	n,
	b
};

typedef struct	s_form
{
	int 		hash;
	int 		zero;
	int 		plus;
	int 		minus;
	int 		space;
	int 		quote;
	int 		dolla;
	int 		width;
	int 		press;
	int			len;
	int 		type;
	void 		*arg;
	char 		*out;
}				t_form;

int				ft_printf(const char *format, ...);
int 			check_flags(char c);
int				check_dolla(char *format, t_form *form);
char			*find_flags(char *format, va_list argc, t_form *form, int *i);
char			*find_type(char *format, va_list argc, t_form *form, int *i);

#endif