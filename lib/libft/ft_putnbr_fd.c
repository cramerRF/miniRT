/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:06:29 by valonso           #+#    #+#             */
/*   Updated: 2021/11/11 19:25:06 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_fd_aux(long int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n < 10)
		ft_putchar_fd('0' + n, fd);
	else
	{
		ft_putnbr_fd_aux(n / 10, fd);
		ft_putnbr_fd_aux(n % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (!fd)
		return ;
	ft_putnbr_fd_aux(n, fd);
}
