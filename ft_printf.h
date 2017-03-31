/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 02:52:07 by akaplyar          #+#    #+#             */
/*   Updated: 2017/03/31 02:53:27 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <stddef.h>
# include <wchar.h>
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
	r,
	n,
	b
};

typedef struct	s_form
{
	int			hash;
	int			zero;
	int			plus;
	int			minus;
	int			space;
	int			quote;
	int			dolla;
	int			width;
	int			press;
	int			len;
	int			type;
	int			sign;
	int			cl;
	int			fd;
	int			nul;
	char		*out;
}				t_form;

int				ft_printf(const char *format, ...);
int				check_type(t_form *form);
int				check_flags(char c);
char			*parse_percent(char *format, va_list argc, va_list tmp,
								t_form *form);
char			*parse_brackets(char *format, t_form *form, va_list argc,
								int *fd);
char			*ft_llitoa_base(uintmax_t value, int base);
char			*find_dolla(char *format, t_form *form);
char			*find_type(char *format, t_form *form);
char			*make_line(char *format, int *size);
char			*ft_llitoa(intmax_t value);
void			parse_int(t_form *form, va_list argc, int *size, int type);
void			print_non_printable(t_form *form, va_list argc, int *size);
void			skip_va_list(va_list argc, va_list tmp, t_form *form);
void			parse_pointer(t_form *form, va_list argc, int *size);
void			print_memory(t_form *form, va_list argc, int *size);
void			parse_wstr(t_form *form, va_list argc, int *size);
void			get_wchar(t_form *form, va_list argc, int *size);
void			parse_str(t_form *form, va_list argc, int *size);
void			fill_hash_u(t_form *form, int mode);
void			fill_quote(t_form *form);
void			fill_width(t_form *form);
void			fill_zero(t_form *form);
void			fill_sign(t_form *form);

#endif
