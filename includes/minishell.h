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

// # include "parsing.h"

# define PROMPT "minishell$ "

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

int	exit_status;
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
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	char    *input;
	char	**input_strings;
	t_envp  *envp_ll;
}	t_data;

// envp_ll.c
t_envp	*init_envp_ll(char **envp);
t_envp	*create_envp_node(char **data);
t_envp	*ft_envp_last(t_envp *lst);
void	ft_envp_add_back(t_envp **lst, t_envp *new);

// main.c
int		main(int ac, char **av, char **envp);

// welcome.c
void	welcome(int argc, char **argv);
//////////////////////////////////////////

enum	e_token_types
{
	WORD, //0
	SEP, // 1
	PIPE, // 2
	IN_RED, // 3
	OUT_RED, // 4
	HERE_DOC, // 5
	APPEND_RED, //6
};

//early_err.c
int		opening_pipe_err(char *input);
int		newline_err(char *input);
int		early_err(t_data *data);

//unsupported_err.c
int		unsupported_quotes_err(char *s);
int		unsupported_char_err(char *input);
int		unsupported_pipe_err(char *input);
int		unsupported_redir_err(char *input, char c);

//input_handler.c
void	manipulate_input(char **input);
int		input_handler(t_data *data);

//manipulate input
int		ft_isspace(char c);
void	unify_spaces(char **input);
void	remove_extra_spaces(char **input);
void	attach_redirect(char **input);
void	add_space_before_redirect(char **input);


//quotes_utils
int		quotes_are_closed(char c);
void	quotes_default(void);

// modified split
char	**shell_split(char *input, char delimiter);
int		str_counter(char *input, char delimiter);
char	*init_str(char *input, char delimiter);
char	**shell_split_remove_spaces(char *input);

// parser.c

void	tokenizer(t_token **token_ll, char *input);

int parser(t_data *data);


t_token	*init_in_quotes(char *s, int *i, char q);
t_token	*init_pipe_or_sep(char *s, int *i, char p_or_s);
t_token	*init_single_redirection(char *s, int *i, char in_or_out);
t_token	*init_double_redirection(char *s, int *i, char in_or_out);
t_token	*init_word(char *s, int *i);

t_token	*token_last(t_token *list);
void	token_add_back(t_token **list, t_token *new);
void	remove_quotes(char *s);
void	remove_quotes_helper(char *s, char q, int *i, int *j);


int	skip_spaces(char *str);
int	skip_quotes(char *str, char quote);
int	find_end(char *str, char *possible_sep);
#endif