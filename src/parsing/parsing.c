/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:23:46 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/11 16:58:00 by abourdon         ###   ########.fr       */
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
	if (check_fine_cote(ms->line, '\'', '\"') == ERR)//check aussi si les chevrons sont valides
	{
		write(2, "dquote\n", 7);
		return (NULL);
	}
	
	ms->split_pipe = split_incurve(ms->line, '|');//PB split sur pipe mais pas si pipe est entre des cotes (faire un split_pipe)
	double_tab = parsing(ms->split_pipe[0], &ms);//si pb cote ou pb dans la commande le double tab dans la liste = NULL
	cmd_lst = lstnew(double_tab, ms->infile_name, ms->outfile_name);// open("chaine que renvoie parsing en fonction des chevron", Ouverture selon les chevron));//fd de -1 si rien a ouvris donc dans la liste on aura -1
	while (ms->split_pipe[i] != NULL)
	{
		double_tab = parsing(ms->split_pipe[i], &ms);
		temp = lstnew(double_tab, ms->infile_name, ms->outfile_name);//Proteger si pb
		lstadd_back(&cmd_lst, temp);
		i++;
	}
	free(ms->split_pipe);
	return (cmd_lst);
}



char	**parsing(char	*one_cmd, t_ms **ms)
{
	char	**double_tab;

	double_tab = NULL;
	if (check_fine_cote(one_cmd, '\'', '\"') == 0)
	{
		one_cmd = strspace_cpy(one_cmd, 0);
		if (exist_chevron(one_cmd) = ERR)
		{
			(*ms)->infile_name = 
			(*ms)->outfile_name = find_outfile(one_cmd, 0)
		}
		else
		{
			(*ms)->infile_name = NULL;
			(*ms)->outfile_name = NULL;
		}
		//Gerer les chevrons. Si entre cote on prend pas en compte. En fonction du sens
		//on connait le mode d'ouverture qu'on stocke quleque part (structure ms).
		//Et ensuite on regarde le nom du fichier qu'on stocke dans une chaine qui sera dans une
		//structure (ms)
		//Si << pas de nom de fichier on utilise here doc et le limiter et le mot juste apres <<
		if (check_cote(one_cmd, '\'') == ERR && check_cote(one_cmd, '\"') == ERR)//Pas de cote
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