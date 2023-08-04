/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:01:23 by valonso           #+#    #+#             */
/*   Updated: 2021/11/11 20:18:48 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*memcpy_back(void *dest, const void *src, size_t n)
{
	if (n == 0 || dest == src)
		return (dest);
	while (n--)
		((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	if (dest > src)
		memcpy_back(dest, src, len);
	else if (dest < src)
		ft_memcpy(dest, src, len);
	return (dest);
}
