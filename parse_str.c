#include "ft_printf.h"

static void		cast_char(t_form *form, wchar_t **wstr, char **cstr)
{
	if (form->type == c || form->type == C)
	{
		**cstr = (char)form->arg;
		**wstr = (wchar_t)form->arg;
	}
	else
	{
		*cstr = (char*)form->arg;
		*wstr = (wchar_t*)form->arg;
	}
}

void			parse_str(t_form *form, char **str)
{
	wchar_t 	*wstr;
	char		*cstr;

	cast_char(form, &wstr, &cstr);
	if (form->type == c)
}