/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:41:37 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/10 13:11:48 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n, int *len, int fd)
{
	if (n == -2147483648)
		ft_putstr("-2147483648", len, fd);
	else
	{
		if (n < 0)
		{
			if (ft_putchar_fd_printf('-', len, fd) == -2)
				return (-2);
			n = n * -1;
		}
		if (n > 9)
		{
			ft_putnbr(n / 10, len, fd);
		}
		if (ft_putchar_fd_printf((n % 10) + 48, len, fd) == -2)
			return (-2);
	}
	return (0);
}
