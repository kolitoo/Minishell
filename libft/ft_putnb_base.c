/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnb_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:34:42 by abourdon          #+#    #+#             */
/*   Updated: 2023/04/05 11:14:49 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnb_base(unsigned int n, char *base, int *len, int fd)
{
	if (n > 15)
	{
		ft_putnb_base(n / 16, base, len, fd);
	}
	ft_putchar_fd_printf(base[n % 16], len, fd);
}
