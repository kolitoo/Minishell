/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:23:46 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/09 17:35:21 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_fine_cote(char *line, char c, char cote)
{
	int	i;
	int	k;

	i = 0;
	k = 1;
	while (line[i] != '\0')
	{
		if (line[i] == cote)
			k = k * -1;
		if (line[i] == c && k > 0)
		{
			i++;
			while (line[i] != c)
			{
				i++;
				if (line[i] == '\0')
					return (1);
			}
		}
		if (line[i] != '\0')
			i++;
	}
	if (k < 0)
		return (1);
	return (0);
}

int	check_cote(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == c)
			return (1);
		i++;
	}
	return (0);
}

t_cmd_lst	*make_cmd_lst(t_ms *ms)
{
	t_cmd_lst	*cmd_lst;
	t_cmd_lst	*temp;
	char	**double_tab;
	int	i;

	i = 1;
	//Ici on fait le split de '|' et on parse chaque commande comme il faut en gerant les cotes etc
	//On met le tout dans un doubleau tableau
	//Puis on cree et on met dans la liste
	if (check_fine_cote(ms->line, '\'', '\"') == 1)
	{
		write(2, "dquote\n", 7);
		return (NULL);
	}
	ms->split_pipe = split_incurve(ms->line, '|');//PB split sur pipe mais pas si pipe est entre des cotes (faire un split_pipe)
	double_tab = parsing(ms->split_pipe[0]);//si pb cote ou pb dans la commande le double tab dans la liste = NULL
	cmd_lst = lstnew(double_tab, 1); //modifier le fd
	while (ms->split_pipe[i] != NULL)
	{
		double_tab = parsing(ms->split_pipe[i]);
		temp = lstnew(double_tab, 1);//Proteger si pb
		lstadd_back(&cmd_lst, temp);
		i++;
	}
	free(ms->split_pipe);
	return (cmd_lst);
}

char	**parsing(char	*one_cmd)
{
	char	**double_tab;
	//Ici on travail avec chaque commande + option pour le mettre correctement en forme dans un
	//double tableau
	double_tab = NULL;
	if (check_fine_cote(one_cmd, '\'', '\"') == 0)
	{
		one_cmd = strspace_cpy(one_cmd, 0);
		if (check_cote(one_cmd, '\'') == 0 && check_cote(one_cmd, '\"') == 0)//Pas de cote
		{
			double_tab = ft_split(one_cmd, ' ');//split normal sur les espaces
		}
		else//Cote
		{
			//split incurve sur tout les espaces sauf interieur des simple/double cotes
			double_tab = split_incurve(one_cmd, ' ');
		}
	}
	else
	{
		write(2, "Probleme cote\n", 15);
	}
	free(one_cmd);//Free de tout le ms.split_pipe
	return (double_tab);
}