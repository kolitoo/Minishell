/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:09:46 by lgirault          #+#    #+#             */
/*   Updated: 2022/11/23 10:49:35 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	e;

	i = 0;
	e = 0;
	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dest[i] != '\0' && i < size)
	{
		i++;
		j++;
	}
	while (i < size - 1 && src[e] != '\0')
	{
		dest[i] = src[e];
		i++;
		e++;
	}
	if (j < size)
		dest[i] = '\0';
	return (j + ft_strlen(src));
}
