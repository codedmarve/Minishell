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
// # include <sys/wait.h>
// # include <string.h>
# include <stdbool.h>
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

// typedef enum token_type {
// 	SPACE
// } 	t_token_type;

enum e_q_status {
	NONE_OR_CLOSED,
	SINGLE_Q,
	DOUBLE_Q
};

/* 
enum (enumneration) is a user defined data tyoe in C.
https://www.geeksforgeeks.org/enumeration-enum-c/

the names make a program easy to read and maintain.

each field of this data_type will be assigned an index

since i will use index for return value, 
i assign spaces to RANDOM NUMBER, so in case of unsuccess i can return 0
and be able to separate success from unsuccess

any field of enum can be assigned to number,
next one will be assigned to number +1


*/

enum	e_token_type
{
	WORD,
	SEP,
	PIPE,
	IN_RED,
	OUT_RED,
	HERE_DOC,
	APPEND_RED,
};


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
	// char *raw_input;

	// int last_exit_code;

	// int		i;
	// int		pid;
	// char	*tmp;
	// char	*path;
	// char	*line;
	// char	*prompt;
	// char	**cmd;
	// char	**prenv;
	// char	**env;
	bool s_quotes_open;
	bool d_quotes_open;
	int idx;
}	t_data;

typedef struct s_token
{
	char			*str;

	int				type; // int we got in enum
	struct s_token	*next;
}	t_token;

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
// prompt.c
char	*get_prompt(void);

// ./lexer

// ./parsing

// ./builtins

int	all_quotes_closed(char *str); 
int input_handler(char *input);

#endif