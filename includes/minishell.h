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
# include <sys/wait.h>
// # include <string.h>

// PATH_MAX -  Maximum number of bytes in a pathname, 
// including the terminating null character. 

# define PROMPT "minishell$ "
# define PIPE '|'
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define IN '<'
# define OUT '>'
# define APP ">>"
// here-document 
// askubuntu.com/questions/678915/whats-the-difference-between-and-in-bash
# define HERE_D "<<"

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
	int		last_exit_code;
	
	int		i;
	char	*path;
	char	*input;
	char	**env;
	char	**cmd;
	char	**prenv;
	char	*tmp;

	// int		pid;
	// char	*line;
	// char	*prompt;
}	t_data;

typedef struct s_token
{
	char			*str;
	int				type;
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