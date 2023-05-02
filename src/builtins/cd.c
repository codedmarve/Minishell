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
		return ;
	}
	if (arrlen(str) == 1)
	{
		if (chdir("~"))
			perror("-bash ");
		return ;
	}
	if (chdir(str[1]))
		perror("-bash ");
}
