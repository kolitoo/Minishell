/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:58:03 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/05 11:14:43 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_modulo_check(char c, va_list arg, int *len, int fd)
{
	char	ch;

	if (c == 'c')
	{
		ch = (char) va_arg(arg, int);
		ft_putchar_fd_printf(ch, len, fd);
	}
	else if (c == 's')
		ft_putstr((char *) va_arg(arg, char *), len, fd);
	else if (c == 'p')
		ft_putvoid((void *) va_arg(arg, void *), len, fd);
	else if (c == 'd' || c == 'i')
		ft_putnbr((int) va_arg(arg, int), len, fd);
	else if (c == 'u')
		ft_putnbr_unsi((unsigned int) va_arg(arg, unsigned int), len, fd);
	else if (c == 'x')
		ft_putnb_base((int) va_arg(arg, int), "0123456789abcdef", len, fd);
	else if (c == 'X')
		ft_putnb_base((int) va_arg(arg, int), "0123456789ABCDEF", len, fd);
	else if (c == '%')
		ft_putchar_fd_printf('%', len, fd);
}

int	ft_printf(int fd, const char *str, ...)
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
			ft_modulo_check(str[i], arg, &len, fd);
		}
		else
		{
			ft_putchar_fd_printf(str[i], &len, fd);
		}
		if (str[i] != '\0')
			i++;
	}
	va_end(arg);
	return (len);
}
