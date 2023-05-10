/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnb_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:34:42 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/10 13:12:04 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnb_base(unsigned int n, char *base, int *len, int fd)
{
	if (n > 15)
	{
		ft_putnb_base(n / 16, base, len, fd);
	}
	if (ft_putchar_fd_printf(base[n % 16], len, fd) == -2)
		return (-2);
	return (0);
}
