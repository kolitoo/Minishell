/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnb_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:34:42 by abourdon          #+#    #+#             */
/*   Updated: 2023/01/19 11:53:54 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnb_base(unsigned int n, char *base, int *len)
{
	if (n > 15)
	{
		ft_putnb_base(n / 16, base, len);
	}
	ft_putchar(base[n % 16], len);
}
