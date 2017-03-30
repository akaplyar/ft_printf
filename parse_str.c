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

static void		wchar_parse(wchar_t w, char *str)
{
	if (w < 0x80)
		*str = (char)w;
	else if (w < 0x0800)
	{
		*str = (char)((w >> 6) | 0xC0);
		*(str + 1) = (char)((w & 0x3F) | 0x80);
	}
	else if (w < 0x10000)
	{
		*str = (char)((w >> 12) | 0xE0);
		*(str + 1) = (char)(((w >> 6) & 0x3F) | 0x80);
		*(str + 2) = (char)((w & 0x3F) | 0x80);
	}
	else if (w < 110000)
	{
		*str = (char)(((w >> 18)) | 0xF0);
		*(str + 1) = (char)(((w >> 12) & 0x3F) | 0x80);
		*(str + 2) = (char)(((w >> 6) & 0x3F) | 0x80);
		*(str + 3) = (char)((w & 0x3F) | 0x80);
	}
}

static void		get_char(t_form *form, va_list argc, char **str)
{
	wchar_t			w;
	char			*tmp;

	tmp = *str;
	if (form->type != c)
	{
		if (form->type == c)
			form->out = ft_strsub(va_arg(argc, const char*), 0, 1);
		else
			form->out = ft_strsub(form->out, 0, 1);
	}
	else
	{
		w = va_arg(argc, wchar_t);
		form->out = ft_strnew(4);
		wchar_parse(w, form->out);
	}
	if (form->type == c && (*form->out < 32))
		form->kostyl += write(1, form->out, 1);
	g_kostyl += form->kostyl;
	fill_width(form);
	*str = ft_strjoin(tmp, form->out);
	free(tmp);
	free(form->out);
}

static void		parse_wstr(t_form *form, va_list argc, char **str)
{
	wchar_t		*wstr;
	char		*cstr;
	char		*tmp;

	form->out = ft_strnew(1);
	wstr = va_arg(argc, wchar_t*);
	cstr = ft_strnew(4);
	while (*wstr)
	{
		wchar_parse(*wstr, cstr);
		if (form->press >= 0)
			if (ft_strlen(cstr) + ft_strlen(form->out) < (size_t)form->press)
				break ;
		tmp = form->out;
		form->out = ft_strjoin(tmp, cstr);
		free(tmp);
		ft_bzero(cstr, 5);
		wstr++;
	}
	tmp = *str;
	fill_width(form);
	*str = ft_strjoin(tmp, form->out);
	free(tmp);
	free(form->out);
}

void			parse_str(t_form *form, va_list argc, char **str)
{
	char		*ptr;

	if (form->type == S)
		parse_wstr(form, argc, str);
	else if (form->type == c || form->type == C || form->type < 0)
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