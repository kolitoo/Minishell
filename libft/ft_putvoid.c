/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putvoid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:17:08 by abourdon          #+#    #+#             */
/*   Updated: 2023/04/05 11:14:58 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_hexa_long(unsigned long n, char *base, int *len, int fd)
{
	if (n > 15)
	{
		ft_putnbr_hexa_long(n / 16, base, len, fd);
	}
	ft_putchar_fd_printf(base[n % 16], len, fd);
}

void	ft_putvoid(void *ptr, int *len, int fd)
{
	unsigned long	i;

	if (!ptr)
	{
		write (1, "(nil)", 5);
		*len = *len + 5;
	}
	else
	{
		i = (unsigned long) ptr;
		ft_putchar_fd_printf('0', len, fd);
		ft_putchar_fd_printf('x', len, fd);
		ft_putnbr_hexa_long(i, "0123456789abcdef", len, fd);
	}
}
