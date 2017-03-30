#include "ft_printf.h"

static void		wchar_parse(wint_t w, char *str)
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

void			get_wchar(t_form *form, va_list argc, int *size)
{
	wchar_t			w;
	char			zero;

	zero = '\0';
	w = (wchar_t)va_arg(argc, wint_t);
	form->out = ft_strnew(4);
	wchar_parse(w, form->out);
	if (*form->out < 32 && *form->out > -1)
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

void			parse_wstr(t_form *form, va_list argc, int *size)
{
	wchar_t		*wstr;
	char		*cstr;
	char		*tmp;

	form->out = ft_strnew(1);
	if (!(wstr = va_arg(argc, wchar_t*)))
		wstr = (wchar_t *)L"(null)";
	cstr = ft_strnew(4);
	while (*wstr)
	{
		wchar_parse(*wstr, cstr);
		if (form->press >= 0)
			if (ft_strlen(cstr) + ft_strlen(form->out) > (size_t)form->press)
				break ;
		tmp = form->out;
		form->out = ft_strjoin(tmp, cstr);
		free(tmp);
		ft_bzero(cstr, 5);
		wstr++;
	}
	fill_width(form);
	*size += write(1, form->out, ft_strlen(form->out));
	free(form->out);
}