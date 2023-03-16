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
// # include <readline/history.h>
# include "../library/libft/libft.h"
// # include <sys/wait.h>
// # include <string.h>

typedef struct s_data
{
	char	**envp;

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

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}	t_token;

// main.c
int		main(int ac, char **av, char **envp);
// welcome.c
void	welcome(int argc, char **argv);
// prompt.c
char	*get_prompt(void);
// envp.c
int		envp_size(char **envp);
char	**envp_copy(t_data *data, char **envp);

// ./lexer

// ./parsing

// ./builtins



void	init_null(t_data *data, char *pwd);

#endif