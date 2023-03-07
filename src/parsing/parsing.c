/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:23:46 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/07 19:16:04 by lgirault         ###   ########.fr       */
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

t_cmd_lst	*lstnew(char **double_tab, int fd)
{
	t_cmd_lst	*a;
	int	i;
	int	j;

	a = malloc(sizeof(*a));
	if (a == NULL)
		return (NULL);
	a->cmd_option = double_tab;
	a->fd = fd;
	a->next = NULL;
	return (a);
}

void	lstadd_back(t_cmd_lst **lst, t_cmd_lst *new)
{
	t_cmd_lst	*ptr;

	ptr = *lst;
	if (lst != NULL)
	{
		if (*lst != NULL)
		{
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = new;
		}
		else
			*lst = new;
	}
}

t_cmd_lst	make_cmd_lst(t_ms *ms)
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
		double_tab = parsing(ms->split_pipe[i]);
		temp = lstnew(double_tab, fd);
		lstadd_back(&cmd_lst, temp);
		i++;
	}
	
}

char	**parsing(char	*one_pipe)
{
	char	**double_tab;
	//Ici on travail avec chaque partie d'un pipe pour le mettre correctement en forme dans un
	//double tableau

	if (check_fine_cote(one_pipe, '\'') == 0 && check_fine_cote(one_pipe, '\"') == 0)
	{
		one_pipe = strspace_cpy(one_pipe, 0);
		ft_printf("line = %s\n", one_pipe);
		if (check_cote(one_pipe, '\'') == 0 && check_cote(one_pipe, '\"') == 0)
		{
			
		}
		else
		{
			
		}
	}
	else
	{
		write(2, "Probleme cote\n", 15);
	}
}