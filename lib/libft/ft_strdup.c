/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:01:38 by valonso           #+#    #+#             */
/*   Updated: 2021/11/11 19:47:05 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*r;

	len = ft_strlen(s);
	r = malloc(++len);
	if (!r)
		return (0);
	i = -1;
	while (++i < len)
		r[i] = (char) s[i];
	return (r);
}
