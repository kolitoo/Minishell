/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:23:46 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/07 19:49:17 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_fine_cote(char *line, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 1;
	while (line[i] != '\0')
	{
		if (line[i] == c)
			k = k * -1;
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
	ms->split_pipe = ft_split(ms->line, '|');//si pas de pipe ?
	double_tab = parsing(ms->split_pipe[0]);//si pas de pipe ?
	cmd_lst = lstnew(double_tab, fd);
	while (ms->split_pipe[i] != NULL)
	{
		//free(double_tab) ou pas ?
		double_tab = parsing(ms->split_pipe[i]);
		temp = lstnew(double_tab, fd);//Proteger si pb
		lstadd_back(&cmd_lst, temp);
		i++;
	}
	//free(double_tab) ou pas ?
	return (cmd_lst);
}

char	**parsing(char	*one_cmd)
{
	char	**double_tab;
	//Ici on travail avec chaque commande + option pour le mettre correctement en forme dans un
	//double tableau

	if (check_fine_cote(one_cmd, '\'') == 0 && check_fine_cote(one_cmd, '\"') == 0)
	{
		one_cmd = strspace_cpy(one_cmd, 0);
		ft_printf("line = %s\n", one_cmd);
		if (check_cote(one_cmd, '\'') == 0 && check_cote(one_cmd, '\"') == 0)//Pas de cote
		{
			double_tab = ft_split(one_cmd, ' ');//split normal sur les espaces
		}
		else//Cote
		{
			//split incurve sur tout les espaces sauf interieur des simple/double cotes
			//ATTENTION juste pour echo cote ou pas cote plein espace ou 1 ca met juste un espace
		}
	}
	else
	{
		write(2, "Probleme cote\n", 15);
	}
}