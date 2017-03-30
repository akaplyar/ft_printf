#include "ft_printf.h"

static void		cut_press(t_form *form)
{
	char	*tmp;
	size_t	press;

	if (form->press < 0)
		return ;
	press = (size_t)form->press;
	if (ft_strlen(form->out) <= press)
		return ;
	tmp = form->out;
	form->out = ft_strsub(tmp, 0, press);
	free(tmp);
}



static void		get_char(t_form *form, va_list argc, char **str)
{
	char			*tmp;
	char			ctmp;

	if (form->type == c)
	{
		ctmp = (char)va_arg(argc, int);
		form->out = ft_strsub(&ctmp, 0, 1);
	}
	else
		form->out = ft_strsub(form->out, 0, 1);
	if (form->type == c && *form->out < 32 && *form->out > -1)
		form->kostyl += 1;
	g_kostyl += form->kostyl;
	fill_width(form);
	tmp = *str;
	*str = ft_strjoin(tmp, form->out);
	free(tmp);
	free(form->out);
}



void			parse_str(t_form *form, va_list argc, char **str)
{
	char		*ptr;

	if (form->type == S)
		parse_wstr(form, argc, str);
	else if (form->type == C)
		get_wchar(form, argc, str);
	else if (form->type == c || form->type < 0)
		get_char(form, argc, str);
	else
	{
		ptr = va_arg(argc, char*);
		if (!ptr)
			form->out = ft_strdup("(null)");
		else
			form->out = ft_strdup(ptr);
		cut_press(form);
		fill_width(form);
		ptr = *str;
		*str = ft_strjoin(ptr, form->out);
		free(ptr);
	}
}