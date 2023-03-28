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
# include "../library/libft/libft.h"
# include <stdbool.h>
# include <sys/wait.h>
// # include <string.h>

// PATH_MAX -  Maximum number of bytes in a pathname, 
// including the terminating null character. 

# define PROMPT "minishell$ "

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

typedef struct s_envp
{
	char			*envp_key;
	char			*envp_value;
	struct s_envp	*next;
}					t_envp;

typedef struct s_data
{
	t_envp  *envp_ll;
	char	**envp_arr;
	char    *input; // SHOULD WE PLACE IT HERE OR SOMEWHERE ELSE???????

	// int last_exit_code;
	int		last_exit_code;
	
	int		i;
	char	*path;
	char	**env;
	char	**cmd;
	char	**prenv;
	char	*tmp;

	// int		pid;
	// char	*line;
	// char	*prompt;
}	t_data;

// typedef struct s_token
// {
// 	char			*str;

// 	int				type; // int we got in enum
// 	struct s_token	*next;
// }	t_token;

// typedef struct s_cmd
// {
// 	char	*path_cmd;
// 	char	**cmd_args;
// }				t_cmd;

// envp - saving envp as a linked list
t_envp	*init_envp_ll(char **envp);
t_envp	*create_envp_node(char **data);
t_envp	*ft_envp_last(t_envp *lst);
void	ft_envp_add_back(t_envp **lst, t_envp *new);

int		init_envp_arr(t_data *data, char **envp);
int		envp_variable_counter(char **envp);


// main.c
int		main(int ac, char **av, char **envp);
// welcome.c
void	welcome(int argc, char **argv);

// ./lexer

// ./parsing

// ./builtins


int 	input_handler(t_data *data, char *input);


// simple case
int		is_simple(char *str);
int		arrlen(char **arr);
void	ft_clarr(char **str);
void	init_null(t_data *data);
int		simple_t(t_data *data);
void	execute(t_data *data);
int		get_path(t_data *data);
void	add_path(t_data *data);
void	ft_clear(t_data *data);

#endif