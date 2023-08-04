/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:16:20 by valonso           #+#    #+#             */
/*   Updated: 2021/11/11 20:12:53 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*out;
	t_list	*aux;

	if (!f || !lst)
		return (0);
	out = 0;
	while (lst)
	{
		aux = ft_lstnew(f(lst->content));
		if (!aux)
			ft_lstclear(&out, del);
		ft_lstadd_back(&out, aux);
		lst = lst->next;
	}
	return (out);
}
