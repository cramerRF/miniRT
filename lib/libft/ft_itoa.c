/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:06:16 by valonso           #+#    #+#             */
/*   Updated: 2021/11/11 18:34:01 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*zero_aux(void)
{
	char	*s;

	s = malloc(2);
	if (!s)
		return (0);
	s[0] = '0';
	s[1] = '\0';
	return (s);
}

char	*nbr_aux(long int i, long int nbr, long int k, long int minus)
{
	char	*s;

	s = malloc(i + minus);
	if (!s)
		return (0);
	i = 0;
	if (minus)
		s[i++] = '-';
	k /= 10;
	while (k)
	{
		s[i++] = nbr / k + '0';
		nbr %= k;
		k /= 10;
	}
	s[i] = 0;
	return (s);
}

char	*ft_itoa(int n)
{
	long int	nbr;
	long int	i;
	long int	k;
	long int	minus;

	nbr = n;
	minus = 0;
	if (n == 0)
		return (zero_aux());
	if (nbr < 0)
	{
		minus = 1;
		nbr = -nbr;
	}
	i = 1;
	k = 1;
	while (nbr / k)
	{
		k *= 10;
		i++;
	}
	return (nbr_aux(i, nbr, k, minus));
}
