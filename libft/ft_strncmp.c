/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:01:45 by lgirault          #+#    #+#             */
/*   Updated: 2022/11/21 11:20:51 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*st1;
	unsigned char	*st2;
	size_t			i;
	size_t			j;

	st1 = (unsigned char *) s1;
	st2 = (unsigned char *) s2;
	i = 0;
	j = 1;
	while (j < n && st1[i] == st2[i] && st1[i] != '\0' && st2[i] != '\0')
	{
		i++;
		j++;
	}
	if (n == 0)
		return (0);
	if (st1[i] != st2[i])
		return (st1[i] - st2[i]);
	return (0);
}
