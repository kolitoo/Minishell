/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:58:03 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 13:10:20 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_modulo_check3(char c, va_list arg, int *len, int fd)
{
	if (c == 'X')
	{
		if (ft_putnb_base((int) va_arg(arg, int),
				"0123456789ABCDEF", len, fd) == -2)
			return (-2);
	}
	else if (c == '%')
	{
		if (ft_putchar_fd_printf('%', len, fd) == -2)
			return (-2);
	}
	return (0);
}

static int	ft_modulo_check2(char c, va_list arg, int *len, int fd)
{
	if (c == 'd' || c == 'i')
	{
		if (ft_putnbr((int) va_arg(arg, int), len, fd) == -2)
			return (-2);
	}
	else if (c == 'u')
	{
		if (ft_putnbr_unsi((unsigned int)
				va_arg(arg, unsigned int), len, fd) == -2)
			return (-2);
	}
	else if (c == 'x')
	{
		if (ft_putnb_base((int) va_arg(arg, int),
				"0123456789abcdef", len, fd) == -2)
			return (-2);
	}
	return (0);
}

static int	ft_modulo_check(char c, va_list arg, int *len, int fd)
{
	char	ch;

	if (c == 'c')
	{
		ch = (char) va_arg(arg, int);
		if (ft_putchar_fd_printf(ch, len, fd) == -2)
			return (-2);
	}
	else if (c == 's')
	{
		if (ft_putstr((char *) va_arg(arg, char *), len, fd) == -2)
			return (-2);
	}
	else if (c == 'p')
	{
		if (ft_putvoid((void *) va_arg(arg, void *), len, fd) == -2)
			return (-2);
	}
	if (ft_modulo_check2(c, arg, len, fd) == -2)
		return (-2);
	if (ft_modulo_check3(c, arg, len, fd) == -2)
		return (2);
	return (0);
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
			if (ft_modulo_check(str[i], arg, &len, fd) == -2)
				return (-2);
		}
		else
		{
			if (ft_putchar_fd_printf(str[i], &len, fd) == -2)
				return (-2);
		}
		if (str[i] != '\0')
			i++;
	}
	va_end(arg);
	return (len);
}
