/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putvoid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:17:08 by abourdon          #+#    #+#             */
/*   Updated: 2023/01/19 11:53:42 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_hexa_long(unsigned long n, char *base, int *len)
{
	if (n > 15)
	{
		ft_putnbr_hexa_long(n / 16, base, len);
	}
	ft_putchar(base[n % 16], len);
}

void	ft_putvoid(void *ptr, int *len)
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
		ft_putchar('0', len);
		ft_putchar('x', len);
		ft_putnbr_hexa_long(i, "0123456789abcdef", len);
	}
}
