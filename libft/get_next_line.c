/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 19:05:33 by akaplyar          #+#    #+#             */
/*   Updated: 2017/02/16 19:05:35 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_mfd	*find_mfd(const size_t fd, t_mfd **begin)
{
	t_mfd	*mfd;

	mfd = *begin;
	while (mfd && mfd->content_size != fd)
		mfd = mfd->next;
	return (mfd);
}

static char		*make_line(int fd, t_mfd **begin)
{
	t_mfd		*mfd;
	char		*str;
	char		*end;
	char		*ptr;

	mfd = find_mfd(fd, begin);
	if (!mfd->content)
		return (NULL);
	if ((end = ft_strchr(mfd->content, '\n')))
	{
		*end = '\0';
		if (!(str = ft_strdup(mfd->content)))
			return (NULL);
		ptr = mfd->content;
		mfd->content = (ft_strlen(end + 1) == 0) ? NULL : ft_strdup(end + 1);
		free(ptr);
	}
	else
	{
		if (!(str = ft_strdup((char*)mfd->content)))
			return (NULL);
		free(mfd->content);
		mfd->content = NULL;
	}
	return (str);
}

static int		make_mfd(int fd, char *buff, t_mfd **begin)
{
	t_mfd		*mfd;
	char		*ptr;

	mfd = find_mfd((size_t)fd, begin);
	if (!mfd)
	{
		if (!(mfd = (t_mfd *)ft_lstnew((void*)buff, (ft_strlen(buff) + 1))))
			return (-1);
		mfd->content_size = (size_t)fd;
		ft_lst_push_back((t_list**)begin, (t_list*)mfd);
	}
	else
	{
		if (!(ptr = ft_strjoin(mfd->content, buff)))
			return (-1);
		free(mfd->content);
		mfd->content = ptr;
	}
	if (ft_strchr(mfd->content, '\n'))
		return (1);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static t_mfd	*begin;
	char			buff[BUFF_SIZE + 1];
	int				ret;
	int				stat;

	if (fd < 0 || !line || read(fd, 0, 0) < 0)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) != 0)
	{
		buff[ret] = '\0';
		if ((stat = make_mfd(fd, buff, &begin)) > 0)
		{
			*line = make_line(fd, &begin);
			return (1);
		}
		if (stat < 0)
			return (-1);
	}
	if ((*line = make_line(fd, &begin)))
		return (1);
	return (0);
}
