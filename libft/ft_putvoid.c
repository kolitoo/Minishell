/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putvoid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:17:08 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/10 13:11:35 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_hexa_long(unsigned long n, char *base, int *len, int fd)
{
	if (n > 15)
	{
		ft_putnbr_hexa_long(n / 16, base, len, fd);
	}
	if (ft_putchar_fd_printf(base[n % 16], len, fd) == -2)
		return (-2);
	return (0);
}

int	ft_putvoid(void *ptr, int *len, int fd)
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
		if (ft_putchar_fd_printf('0', len, fd) == -2)
			return (-2);
		if (ft_putchar_fd_printf('x', len, fd) == -2)
			return (-2);
		if (ft_putnbr_hexa_long(i, "0123456789abcdef", len, fd) == -2)
			return (-2);
	}
	return (0);
}
