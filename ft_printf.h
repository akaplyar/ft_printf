#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <stddef.h>
# include <limits.h>

# include <stdio.h>

enum	e_mode
{
	hh,
	h,
	l,
	ll,
	L,
	j,
	z,
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
	int			sign;
	void 		*arg;
	char 		*out;
}				t_form;

int				ft_printf(const char *format, ...);
int 			check_flags(char c);
int				check_dolla(char *format);
int				check_type(char c, int i);
char			*find_flags(char *format, va_list argc, t_form *form, int *i);
char			*find_type(char *format, va_list argc, t_form *form, int *i);
char			*ft_llitoa(intmax_t value);
char			*ft_ullitoa(uintmax_t value);
char			*ft_llitoa_base(uintmax_t value, int base);
void			fill_zero(t_form *form);
void			fill_sign(t_form *form);
void			fill_width(t_form *form);
void			fill_hash_u(t_form *form, int mode);
void			parse_int(t_form *form, char **str, int *i, int type);
void			parse_str(t_form *form, char **str, int *i, int type);
void			parse_pointer(t_form *form, char **str, int *i, int type);

#endif