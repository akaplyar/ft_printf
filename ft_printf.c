#include "ft_printf.h"

static void			join_line(char *line, char **str)
{
	char			*tmp;

	tmp = *str;
	*str = ft_strjoin(tmp, line);
	free(tmp);
}

static void			parse_args(t_list **head, char **str, int *i)
{
	t_list			*node;
	t_form			*form;
	int				type;

	node = *head;
	while (node)
	{
		if (node->content_size)
		{
			form = (t_form *) node->content;
			type = check_type('\0', form->type);
			if (type == 1 || type == 2)
				parse_int(form, str, i, type);
			else if (type == 3)
				parse_str(form, str, i, type);
			else if (type == 4)
				parse_pointer(form , str, i, type);
		}
		else
			join_line(node->content, str);
		node = node->next;
	}
}

static void			form_init(t_form *form)
{
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
	form->sign = 0;
	form->arg = NULL;
	form->out = NULL;
}

static const char	*parse_format(const char *format, va_list argc, t_list **head)
{
	t_form			form;
	size_t			len;
	t_list			*node;
	int 			i;

	i = 0;
	len = 0;
	if (*format == '%')
	{
		form_init(&form);
		format = find_flags((char*)format, argc, &form, &i);
		format = find_type((char*)format, argc, &form, &i);
		node = ft_lstnew((void*)&form, sizeof(t_form));
		node->content_size = 1;
	}
	else
	{
		len = 1;
		while (*(format + len) != '%')
			len++;
		node = ft_lstnew((void*)format, len);
		node->content_size = 0;
	}
	ft_lst_push_back(head, node);
	return (format + (len == 1 ? 2 : len));
}

int					ft_printf(const char *format, ...)
{
	t_list  *head;
	va_list argc;
	char	*str;
	int		dolla[2];

	str = (char*)ft_memalloc(1);
	dolla[0] = check_dolla((char*)format);
	va_start(argc, format);
	while (*format)
	{
		if (!(format = parse_format(format, argc, &head)))
			return (0);
		if (*format)
			format++;
	}
	va_end(argc);
	parse_args(&head, &str, dolla);
	return (0);
}