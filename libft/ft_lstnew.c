/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 20:41:34 by akaplyar          #+#    #+#             */
/*   Updated: 2017/02/16 17:57:47 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*node;
	void	*ptr;

	if (!(node = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	node->next = NULL;
	if (content)
	{
		if (!(ptr = malloc(content_size)))
		{
			free(node);
			return (NULL);
		}
		node->content = ft_memcpy(ptr, content, content_size);
		node->content_size = content_size;
	}
	else
	{
		node->content = NULL;
		node->content_size = 0;
	}
	return (node);
}
