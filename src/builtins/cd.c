/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:46:13 by moduwole          #+#    #+#             */
/*   Updated: 2023/04/05 12:46:13 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(char **str)
{
	if (arrlen(str) > 2)
	{
		printf("-bash: cd: too many arguments\n");
		g_exit_status = 1;
		return ;
	}
	if (arrlen(str) == 1)
	{
		if (chdir("/home"))
			printf("This feature is only Linux compactible\n");
		g_exit_status = 0;
		return ;
	}
	if (chdir(str[1]))
	{
		printf("-bash: cd: %s: %s\n", str[1], strerror(errno));
		g_exit_status = 1;
		return ;
	}
	g_exit_status = 0;
}
