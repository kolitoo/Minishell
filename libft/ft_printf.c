/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:58:03 by lgirault          #+#    #+#             */
/*   Updated: 2023/01/19 11:54:00 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_modulo_check(char c, va_list arg, int *len)
{
	char	ch;

	if (c == 'c')
	{
		ch = (char) va_arg(arg, int);
		ft_putchar(ch, len);
	}
	else if (c == 's')
		ft_putstr((char *) va_arg(arg, char *), len);
	else if (c == 'p')
		ft_putvoid((void *) va_arg(arg, void *), len);
	else if (c == 'd' || c == 'i')
		ft_putnbr((int) va_arg(arg, int), len);
	else if (c == 'u')
		ft_putnbr_unsi((unsigned int) va_arg(arg, unsigned int), len);
	else if (c == 'x')
		ft_putnb_base((int) va_arg(arg, int), "0123456789abcdef", len);
	else if (c == 'X')
		ft_putnb_base((int) va_arg(arg, int), "0123456789ABCDEF", len);
	else if (c == '%')
		ft_putchar('%', len);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	int		i;
	va_list	arg;

	len = 0;
	i = 0;
	va_start(arg, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			ft_modulo_check(str[i], arg, &len);
		}
		else
		{
			ft_putchar(str[i], &len);
		}
		if (str[i] != '\0')
			i++;
	}
	va_end(arg);
	return (len);
}
