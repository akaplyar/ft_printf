#include "ft_printf.h"

static void		len_cast2(t_form *form, intmax_t *buff, uintmax_t *ubuff)
{
	if (form->len == j)
	{
		*buff = (intmax_t)form->arg;
		*ubuff = (uintmax_t)form->arg;
	}
	else if (form->len == z)
	{
		*buff = (size_t)form->arg;
		*ubuff = (size_t)form->arg;
	}
	else
	{
		*buff = (int)form->arg;
		*ubuff = (unsigned int)form->arg;
	}
}

static void		len_cast(t_form *form, intmax_t *buff, uintmax_t *ubuff)
{
	if (form->len == hh)
	{
		*buff = (short)form->arg;
		*ubuff = (unsigned short)form->arg;
	}
	else if (form->len == h)
	{
		*buff = (char)form->arg;
		*ubuff = (unsigned char)form->arg;
	}
	else if (form->len == l)
	{
		*buff = (long)form->arg;
		*ubuff = (unsigned long)form->arg;
	}
	else if (form->len == ll)
	{
		*buff = (long long)form->arg;
		*ubuff = (unsigned long long)form->arg;
	}
	else
		len_cast2(form, buff, ubuff);
}

static void		apply_flags(t_form *form, char **str, int *i, int type)
{
	char		*tmp;

	tmp = *str;
	if (form->press >= 0)
		fill_zero(form);
	if (form->hash && type == 2)
		fill_hash_u(form, (form->type == x || form->type == X) ? 1 : 0);
	if ((form->sign || form->plus || form->space) && type == 1 && !form->zero)
		fill_sign(form);
	fill_width(form);
	if ((form->sign || form->plus || form->space) && type == 1 && form->zero)
		fill_sign(form);
	if (form->type == X)
		ft_strcapitalizer(form->out);
	*str = ft_strjoin(tmp, form->out);
	free(tmp);
	free(form->out);
}

void			parse_int(t_form *form, char **str, int *i, int type)
{
	intmax_t	buff;
	uintmax_t	ubuff;

	len_cast(form, &buff, &ubuff);
	if (type == 1)
	{
		form->out = ft_llitoa(buff);
		if (buff < 0)
			form->sign = 1;
	}
	else
	{
		if (form->type == u || form->type == U)
			form->out = ft_ullitoa(ubuff);
		else if (form->type == b)
			form->out = ft_llitoa_base(ubuff, 2);
		else if (form->type == o || form->type == O)
			form->out = ft_llitoa_base(ubuff, 8);
		else if (form->type == x || form->type == X)
			form->out = ft_llitoa_base(ubuff, 16);
	}
	apply_flags(form, str, i, type);
}