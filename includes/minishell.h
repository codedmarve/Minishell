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

# include "parsing.h"

# define PROMPT "minishell$ "

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

/*
structure is used to save KEY=VALUE data from ENVP as a linked list
*/

typedef struct s_envp
{
	char			*envp_key;
	char			*envp_value;
	struct s_envp	*next;
}					t_envp;

typedef struct s_token
{
	char			*string;
	int type;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	char    *input;
	t_envp  *envp_ll;
	t_token *token_ll;




}	t_data;

// global struct t_data
// {
// 	*raw_input
// 	t_envp *envp_ll;
// 	char **input_slitted;- 2d array (holds a 2d char array, all the commands, 
// 	arguments,pipes...separated, empty spaces????)

// 	** paths: 2d char array that holds all the paths to the bin folders
//  	* that are saved in the env variable PATH - may be stored inside of the PATH node

// 	amount_of_pipe_groups (pipes+1)
// 	*pipe_groups
// }


// struct pipe_group contains:
// info abt command,
// arguments,
// any input/output redirection or piping
// first *word will be command itself

// handles built-in commands 
// and executable commands
// with their respective 
// paths.

// struct pipe_group
// {
// exit status (here?)
// **words
// *path
// builtin (if builin == ECHO->run ft_echo)

// redirection_in
// char *arr_inputfile

// redirection_out
// char *arr_outputfile

// pipe_in
// pipe_out
// pipe_fd[2]

// pid from executor

// *t_data
// }

// ENVP
// envp_ll.c
t_envp	*init_envp_ll(char **envp);
t_envp	*create_envp_node(char **data);
t_envp	*ft_envp_last(t_envp *lst);
void	ft_envp_add_back(t_envp **lst, t_envp *new);

// main.c
int		main(int ac, char **av, char **envp);
// welcome.c
void	welcome(int argc, char **argv);

#endif