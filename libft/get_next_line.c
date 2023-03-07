/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:51:39 by lgirault          #+#    #+#             */
/*   Updated: 2023/01/19 12:00:31 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_cara(char *str, char c, int boole)
{
	int	i;

	i = 0;
	if (boole == 0)
	{
		while (str[i] != c && str[i] != '\0')
			i++;
		if (str[i] == c)
			return (i + 1);
		return (0);
	}
	else
	{
		while (str[i] == -1)
			i++;
		return (i);
	}
}

void	init_str(char *buff, char c, int boole)
{
	int	i;

	i = 0;
	if (boole == 0)
	{
		while (buff[i] != '\n')
		{
			buff[i] = c;
			i++;
		}
		buff[i] = c;
	}
	else
	{
		while (i <= BUFFER_SIZE)
		{
			buff[i] = c;
			i++;
		}
	}
}

int	no_new_line(char *buff, char **line, int fd, int *red)
{
	*line = join(*line, substr(buff, check_cara(buff, -1, 1),
				check_cara(buff, '\0', 0) - check_cara(buff, -1, 1)));
	init_str(buff, '\0', 1);
	*red = read(fd, buff, BUFFER_SIZE);
	if (*red < 0)
	{
		free(*line);
		return (0);
	}
	return (1);
}

int	init_read(char *buff, char **line, int *red, int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	*line = ft_callocc(1, sizeof(char));
	if (!*line)
		return (0);
	*red = 1;
	if (buff[0] != -1)
	{
		*red = read(fd, buff, BUFFER_SIZE);
		if (*red < 0)
		{
			free(*line);
			return (0);
		}
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	int			red;

	buff[BUFFER_SIZE] = '\0';
	if (init_read(buff, &line, &red, fd) == 0)
		return (NULL);
	while (red != 0)
	{
		if (check_cara(buff, '\n', 0) != 0)
		{
			line = join(line, substr(buff, check_cara(buff, -1, 1),
						check_cara(buff, '\n', 0) - check_cara(buff, -1, 1)));
			init_str(buff, -1, 0);
			return (line);
		}
		if (no_new_line(buff, &line, fd, &red) == 0)
			return (NULL);
	}
	if (free_line(line) == 1)
		return (NULL);
	return (line);
}
