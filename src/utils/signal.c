/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:59:11 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/14 12:28:07 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	handler_sigint(int signal)
// {
// 	(void)signal;
// 	if (ms.here != 1)
// 	{
// 		ft_printf(1, "\n");
// 		ft_printf(1, "\033[36m \033[1m");
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// 	if (ms.here == 1 && ms.filed == 0)
// 	{
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		ms.here = 0;
// 		ms.sig = 1;
// 		close(0);
// 	}
// }