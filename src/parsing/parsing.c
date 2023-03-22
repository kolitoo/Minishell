/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:23:46 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/22 15:50:13 by lgirault         ###   ########.fr       */
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
	if (exist_chevron(one_cmd) == SUC)
	{
		rights_check(one_cmd, ms, '<');
		rights_check(one_cmd, ms, '>');
		(*ms)->split_chevron_out = find_file(one_cmd, '>');
		(*ms)->split_chevron_in = find_file(one_cmd, '<');
		one_cmd = strspace_cpy(one_cmd, 0);
		if (one_cmd == NULL)
			return (NULL);
	}
	else
	{
		(*ms)->split_chevron_in = NULL;
		(*ms)->split_chevron_out = NULL;
	}
	return (one_cmd);
}

char    *clear_quote(char    *str)
{
    int    i;
    int    j;
    int    len;
    char    *newstr;

    i = 0;
    j = 0;
    len = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\"')
        {
            i++;
            while (str[i] != '\"')
            {
                len++;
                i++;
            }
            if (str[i] == '\"')
                i++;
        }
        if (str[i] == '\'')
        {
            i++;
            while (str[i] != '\'')
            {
                len++;
                i++;
            }
            if (str[i] == '\'')
                i++;
        }
        if (str[i] != '\0' && str[i] != '\"' && str[i] != '\'')
        {
            len++;
            i++;
        }
    }
    i = 0;
    newstr = malloc(sizeof(char) * (len + 1));
    while (str[i] != '\0')
    {
        if (str[i] == '\"')
        {
            i++;
            while (str[i] != '\"')
            {
                newstr[j] = str[i];
                i++;
                j++;
            }
            if (str[i] == '\"')
                i++;
        }
        if (str[i] == '\'')
        {
            i++;
            while (str[i] != '\'')
            {
                newstr[j] = str[i];
                i++;
                j++;
            }
            if (str[i] == '\'')
                i++;
        }
        if (str[i] != '\0' && str[i] != '\"' && str[i] != '\'')
        {
            newstr[j] = str[i];
            i++;
            j++;
        }
    }
    newstr[j] = '\0';
    free(str);
    return (newstr);
}

char    **clean_str(char **double_tab)
{
    int    j;

    j = 0;
    while (double_tab[j] != NULL)
    {
        if (check_cote(double_tab[j], '\'') == ERR || check_cote(double_tab[j], '\"') == ERR)
            double_tab[j] = clear_quote(double_tab[j]);
        j++;
    }
    return (double_tab);
}

char	**parsing(char	*one_cmd, t_ms **ms)
{
	char	**double_tab;

	double_tab = NULL;
	if (check_fine_cote(one_cmd, '\'', '\"') == 0)
	{
		one_cmd = strspace_cpy(one_cmd, 0);
		one_cmd = parsing_chevron(one_cmd, ms);
		one_cmd = set_dollar(one_cmd, ms);
		if (nb_cote(one_cmd) == 0)//Pas de cote//faire une fonction pour split_espace
		{
			double_tab = ft_split(one_cmd, ' ');
		}
		else//Cote
		{
			double_tab = split_incurve(one_cmd, ' ');
		}
		double_tab = clean_str(double_tab);
	}
	else
	{
		write(2, "Probleme cote\n", 15);
	}
	free(one_cmd);//Free de tout le ms.split_pipe
	return (double_tab);
}