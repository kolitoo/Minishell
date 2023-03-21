/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:43:02 by lgirault          #+#    #+#             */
/*   Updated: 2022/11/23 11:55:10 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_size(size_t size_str, unsigned int start, size_t len)
{
	if (len > size_str && start > size_str)
		return (1);
	else if (len >= size_str)
		return ((size_str - start) + 1);
	else if (start > len)
		return (1);
	else
		return (len + 1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	e;
	char	*str;

	if (s == NULL)
		return (NULL);
	e = ft_size(ft_strlen(s), start, len);
	str = malloc(e * sizeof(char));
	if (str == NULL)
		return (0);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}
