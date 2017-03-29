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
	int			dolla;
	int 		width;
	int 		press;
	int			len;
	int 		type;
	int			sign;
	int			dl;
	int			cl;
	void 		*arg;
	char 		*out;
}				t_form;

int				ft_printf(const char *format, ...);
int 			check_flags(char c);
int				check_type(int i);
char			*parse_percent(char *format, va_list argc, va_list tmp, t_form *form);
char			*find_type(char *format, va_list argc, t_form *form);
char			*find_dolla(char *format, t_form *form);
char			*ft_llitoa(intmax_t value);
char			*ft_ullitoa(uintmax_t value);
char			*ft_llitoa_base(uintmax_t value, int base);
void			skip_va_list(va_list argc, va_list tmp, t_form *form);
void			fill_zero(t_form *form);
void			fill_sign(t_form *form);
void			fill_width(t_form *form);
void			fill_hash_u(t_form *form, int mode);
void			parse_int(t_form *form, char **str, int type);
void			parse_str(t_form *form, char **str);
void			parse_pointer(t_form *form, char **str, int type);

#endif