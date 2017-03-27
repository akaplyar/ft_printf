#include "ft_printf.h"

static void			parse_type(t_form *form, int *i)
{
	return ;
}

static t_form		*form_init(void)
{
	t_form			*form;

	if (!(form = (t_form*)malloc(sizeof(t_form))))
		return (NULL);
	form->hash = 0;
	form->zero = 0;
	form->plus = 0;
	form->minus = 0;
	form->space = 0;
	form->quote = 0;
	form->dolla = 0;
	form->width = 0;
	form->press = -1;
	form->len = -1;
	form->type = -1;
	form->arg = NULL;
	form->out = NULL;
	return (form);
}

static const char	*parse_format(const char *format, va_list argc, t_list **head)
{
	t_form			*form;
	size_t			len;
	int 			i;

	i = 0;
	if (*format == '%')
	{
		if (!(form = form_init()))
			return (NULL);
		format = find_flags((char*)format, argc, form, &i);
		format = find_type((char*)format, argc, form, &i);
		ft_lst_push_back(head, ft_lstnew((void*)form, sizeof(t_form)));
	}
	else
	{
		len = 1;
		while (*(format + len) != '%')
			len++;
		ft_lst_push_back(head, ft_lstnew((void*)format, len));
	}
	return (format + (len == 1 ? 2 : len));
}

int					ft_printf(const char *format, ...)
{
	t_list  *head;
	va_list argc;

	va_start(argc, format);
	while (*format)
	{
		if (!(format = parse_format(format, argc, &head)))
			return (0);
		if (*format)
			format++;
	}
	va_end(argc);
	return (0);
}