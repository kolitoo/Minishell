/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:23:46 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/14 15:11:12 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd_lst	*make_cmd_lst(t_ms *ms)
{
	t_cmd_lst	*cmd_lst;
	t_cmd_lst	*temp;
	char	**double_tab;
	int	i;

	i = 1;
	ms->outfile_name = NULL;
	ms->infile_name = NULL;
	ms->boolean_infile = 0;
	ms->boolean_outfile = 0;
	if (check_fine_cote(ms->line, '\'', '\"') == ERR)//check aussi si les chevrons sont valides
	{
		write(2, "dquote\n", 7);
		return (NULL);
	}
	if (check_space_chevron(ms->line) == ERR)
	{
		write(2, "chevron\n", 8);
		return (NULL);
	}
	ms->split_pipe = split_incurve(ms->line, '|');//PB split sur pipe mais pas si pipe est entre des cotes (faire un split_pipe)
	double_tab = parsing(ms->split_pipe[0], &ms);//si pb cote ou pb dans la commande le double tab dans la liste = NULL
	cmd_lst = lstnew(double_tab, ms);// open("chaine que renvoie parsing en fonction des chevron", Ouverture selon les chevron));//fd de -1 si rien a ouvris donc dans la liste on aura -1
	while (ms->split_pipe[i] != NULL)
	{
		ms->outfile_name = NULL;
		ms->infile_name = NULL;
		ms->boolean_infile = 0;
		ms->boolean_outfile = 0;
		double_tab = parsing(ms->split_pipe[i], &ms);
		temp = lstnew(double_tab, ms);//Proteger si pb
		lstadd_back(&cmd_lst, temp);
		i++;
	}
	free(ms->split_pipe);
	return (cmd_lst);
}

int	exist_chevron(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '<' || str[i] == '>') && bool_cote(str, i) == 1)
			return (0);
		i++;
	}
	return (1);
}

char	*parsing_chevron(char *one_cmd, t_ms **ms)
{
	int	i;

	i = 0;
	if (exist_chevron(one_cmd) == SUC)
	{
		rights_check(one_cmd, ms, '<');// prendre en compte les droit seulement du dernier fichier
		rights_check(one_cmd, ms, '>');
		//one_cmd = find_infile(one_cmd, ms, 0);//double tab pour les infile et oufile
		if (nb_chevron(one_cmd, '>') == 1)
			one_cmd = find_outfile_one(one_cmd, ms, 0);
		else
			one_cmd = find_outfile(one_cmd, ms);//one_cmd sera dans un des deux. et si on a cat > test < test1 one_cmd sera la ou il reste un chevron
		if (one_cmd == NULL)
			return (NULL);
	}
	else
	{
		(*ms)->infile_name = NULL;
		(*ms)->outfile_name = NULL;
	}
	return (one_cmd);
}

char	**parsing(char	*one_cmd, t_ms **ms)
{
	char	**double_tab;
	int	i;

	i = 0;
	double_tab = NULL;
	if (check_fine_cote(one_cmd, '\'', '\"') == 0)
	{
		one_cmd = strspace_cpy(one_cmd, 0);
		one_cmd = parsing_chevron(one_cmd, ms);
		if (check_cote(one_cmd, '\'') == 0 && check_cote(one_cmd, '\"') == 0)//Pas de cote
		{
			double_tab = ft_split(one_cmd, ' ');
		}
		else//Cote
		{
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