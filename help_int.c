# include "ft_printf.h"

void		fill_hash_u(t_form *form, int mode)
{
	char	*tmp;
	char	*hash;

	hash = mode ? ft_strdup("0x") : ft_strdup("0");
	if (form->zero)
	{
		form->width -= mode ? 2 : 1;
		fill_width(form);
	}
	if (ft_strncmp(form->out, "0", 1) || (form->type != o && form->type != O))
	{
		tmp = form->out;
		form->out = ft_strjoin(hash, tmp);
		free(tmp);
	}
	free(hash);
}

void		fill_width(t_form *form)
{
	size_t	len;
	size_t	width;
	size_t	i;
	char	*tmp;
	char	*filler;

	width = (size_t)form->width;
	len = ft_strlen(form->out) + form->nul;
	if (len >= width)
		return ;
	i = 0;
	tmp = form->out;
	filler = (char*)ft_memalloc(width - len + 1);
	while (i < width - len)
		filler[i++] = (char)(form->zero ? '0' : ' ');
	filler[i] = '\0';
	if (form->minus)
		form->out = ft_strjoin(tmp, filler);
	else
		form->out = ft_strjoin(filler, tmp);
	free(tmp);
	free(filler);
}

void		fill_sign(t_form *form)
{
	char	*tmp;

	if (form->zero)
	{
		form->width -= (form->width ? 1 : 0);
		fill_width(form);
	}
	tmp = form->out;
	if (form->sign)
		form->out = ft_strjoin("-", tmp);
	else if (form->plus)
		form->out = ft_strjoin("+", tmp);
	else
		form->out = ft_strjoin(" ", tmp);
	free(tmp);
}

void		fill_zero(t_form *form)
{
	size_t	len;
	size_t	press;
	size_t	i;
	char	*tmp;
	char	*zero_str;

	press = (size_t)form->press;
	len = ft_strlen(form->out);
	if (press <= len)
		return ;
	zero_str = (char*)ft_memalloc(press - len + 1);
	i = 0;
	while (i < press - len)
		zero_str[i++] = '0';
	tmp = form->out;
	form->out = ft_strjoin(zero_str, tmp);
	free(tmp);
	free(zero_str);
}