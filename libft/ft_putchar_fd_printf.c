/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd_printf.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:44:14 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/10 15:57:14 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_fd_printf(char c, int *len, int fd)
{
	if (write(fd, &c, 1) == -1)
	{
		write(2, "echo: write error: No space left on device\n", 43);
		return (-2);
	}
	*len = *len + 1;
	return (0);
}
