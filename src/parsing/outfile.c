/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:04:32 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/10 14:05:01 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_len(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' && bool_cote(str, i) == 1)
		{
			while (str[i] == '>' || str[i] == ' ')
				i++;
			while (str[i] != ' ' && str[i] != '|' && str[i] != '>' && str[i] != '\0')
			{
				i++;
				j++;
			}
			return (j);
		}
		i++;
	}
	return (0);
}

char	*find_outfile(char *str, int i)
{
	char	*outfile;
	int	j;

	j = 0;
	outfile = malloc(sizeof(char) * ft_len(str, i) + 1);
	if (outfile == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		//printf("test\n");
		if (str[i] == '>' && bool_cote(str, i) == 1)
		{
			while (str[i] == '>' || str[i] == ' ')
				i++;
			while ((str[i] != ' ' && str[i] != '|' && str[i] != '>' && str[i] != '\0') || bool_cote(str, i) == 0)
			{
				outfile[j] = str[i];
				i++;
				j++;
			}
			outfile[j] = '\0';
			return (outfile);
		}
		i++;
	}
	//suppr de str le/les chevrons et les nom du fichier
	return (NULL);
}

int	main(void)
{
	char	*str = ">test";
	printf("%s\n", find_outfile(str, 0));
}