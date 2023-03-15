/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:23:20 by moduwole          #+#    #+#             */
/*   Updated: 2023/03/09 13:23:20 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
// # include "libft.h"
// daria: changed to right include address:
# include "../library/libft/libft.h"
# include <sys/wait.h>
# include <string.h>

typedef struct s_data
{
	char **envp;
	
	// int		i;
	// int		pid;
	// char	*tmp;
	// char	*path;
	// char	*line;
	// char	*prompt;
	// char	**cmd;
	// char	**prenv;
	// char	**env;
}	t_data;

void	welcome(int argc, char **argv);
char	*get_prompt(void);
void	init_null(t_data *data, char *pwd);

#endif