#include "ft_printf.h"

static void		cut_press(t_form *form)
{
	char		*tmp;
	size_t		press;

	if (form->press < 0)
		return ;
	press = (size_t)form->press;
	if (ft_strlen(form->out) <= press)
		return ;
	tmp = form->out;
	form->out = ft_strsub(tmp, 0, press);
	free(tmp);
}



static void		get_char(t_form *form, va_list argc, int *size)
{
	char		ctmp;
	char		zero;

	zero = '\0';
	if (form->type == c || form->type == C)
	{
		ctmp = (form->type == c ? va_arg(argc,  int)
									  : (char)va_arg(argc, wchar_t));
		form->out = ft_strdup(&ctmp);
	}
	else
		form->out = ft_strsub(form->out, 0, 1);
	if ((form->type == c || form->type == C)
		&& *form->out < 32 && *form->out > -1)
		form->nul = 1;
	fill_width(form);
	if (!form->minus)
		*size += write(1, form->out, ft_strlen(form->out));
	if (form->nul)
		*size += write(1, &zero, 1);
	if (form->minus)
		*size += write(1, form->out, ft_strlen(form->out));
	free(form->out);
}


void			parse_str(t_form *form, va_list argc, int *size)
{
	char		*ptr;

	if (form->type == S)
		parse_wstr(form, argc, size);
	else if (form->type == c || form->type == C || form->type < 0)
		get_char(form, argc, size);
	else
	{
		ptr = va_arg(argc, char*);
		if (!ptr)
			form->out = ft_strdup("(null)");
		else
			form->out = ft_strdup(ptr);
		cut_press(form);
		fill_width(form);
		*size += write(1, form->out, ft_strlen(form->out));
	}
}