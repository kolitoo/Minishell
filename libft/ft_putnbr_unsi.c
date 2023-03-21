/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:57:20 by lgirault          #+#    #+#             */
/*   Updated: 2023/01/19 11:53:51 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_unsi(unsigned int n, int *len)
{
	if (n > 9)
	{
		ft_putnbr_unsi(n / 10, len);
	}
	ft_putchar((n % 10) + 48, len);
}
