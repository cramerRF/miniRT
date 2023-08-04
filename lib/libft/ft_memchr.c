/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:01:08 by valonso           #+#    #+#             */
/*   Updated: 2021/11/11 19:43:39 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*aux;
	size_t			i;

	i = -1;
	aux = (unsigned char *) s;
	while (++i < n)
	{
		if (aux[i] == (unsigned char) c)
			return (aux + i);
	}
	return (0);
}
