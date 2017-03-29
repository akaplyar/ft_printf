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

static void		get_wchar(t_form *form, char **str)
{
	wchar_t		w[2];
	char		*ptr;
	char		*tmp;

	w[0] = (wchar_t)form->arg;
	w[1] = '\0';
	tmp = *str;
	ptr = ft_strnew(4);
	wchar_parse(w[0], ptr);
	*str = ft_strjoin(tmp, ptr);
	free(tmp);
	free(ptr);
}

static void		parse_wstr(t_form *form, char **str)
{
	wchar_t		*wstr;
	char		*cstr;
	char		*tmp;

	form->out = ft_strnew(1);
	wstr = (wchar_t*)form->arg;
	cstr = ft_strnew(4);
	while (*wstr)
	{
		wchar_parse(*wstr, cstr);
		if (form->press >= 0)
			if (ft_strlen(cstr) + ft_strlen(form->out) < form->press)
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

void			parse_str(t_form *form, char **str)
{
	char				*ptr;
	unsigned char		ch[2];

	if (form->type == S || form->type == C)
		form->type == S ? parse_wstr(form, str) : get_wchar(form, str);
	else
	{
		ptr = *str;
		if (form->type == c)
		{
			ch[0] = (unsigned char)form->arg;
			ch[1] = '\0';
			*str = ft_strjoin(ptr, (const char*)ch);
		}
		else
		{
			form->out = (char*)form->arg;
			cut_press(form);
			fill_width(form);
			*str = ft_strjoin(ptr, form->out);
		}
		free(ptr);
	}
}