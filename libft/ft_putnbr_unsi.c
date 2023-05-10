/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:57:20 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 13:11:57 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_unsi(unsigned int n, int *len, int fd)
{
	if (n > 9)
	{
		ft_putnbr_unsi(n / 10, len, fd);
	}
	if (ft_putchar_fd_printf((n % 10) + 48, len, fd) == -2)
		return (-2);
	return (0);
}
