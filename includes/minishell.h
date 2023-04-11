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

// int	exit_status;

typedef struct s_envp
{
	char			*envp_key;
	char			*envp_value;
	int				sorted;
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
	char	*input;
	t_envp	*env_ll;




}	t_data;

enum	e_token_types
{
	SEP,
	WORD,
	PIPE,
	IN_RED,
	OUT_RED,
	HERE_DOC,
	APPEND_RED,
};

// envp_ll.c
void	envplist_handler(t_envp **head, char **envp);
t_envp	*create_envp_node(char **data);
void	ft_envp_add_back(t_envp **lst, t_envp *new);
t_envp	*ft_envp_last(t_envp *lst);

char	*ft_strdup2(const char *str, int len);
char	*ft_strdup1(const char *str);
void	print_env(t_data *data);


// main.c
int		main(int ac, char **av, char **envp);

//early_err.c
int		early_err(t_data *data);

//early_err_utils.c
int		pipes_err(char *input);
int		spaces_err(char *input);
int		quotes_err(char *s);
int		spec_char_err(char *input);
int		redirection_err(char *input);

//early_err_utils2.c
int		redirection_err_s_in(char *s, int *i);
int		redirection_err_s_out(char *s, int *i);
int		redirection_err_d_in(char *s, int *i);
int		redirection_err_d_out(char *s, int *i);

//input_handler.c
int		input_handler(t_data *data);

// parser.c
int		parser(t_data *data);

// tokenizer.c
void	tokenizer(t_token **token_ll, char *input);

// tokenizer_init.c
t_token	*init_in_quotes(char *s, int *i, char q);
t_token	*init_pipe_or_sep(char *s, int *i, char p_or_s);
t_token	*init_single_redirection(char *s, int *i, char in_or_out);
t_token	*init_double_redirection(char *s, int *i, char in_or_out);
t_token	*init_word(char *s, int *i);

//tokenizer_utils.c
t_token	*token_last(t_token *lst);
void	token_add_back(t_token **lst, t_token *new);
void	remove_quotes(char *str);
void	remove_quotes_helper(char *str, char quote, int *i, int *j);

//utils.c
int		skip_spaces(char *str);
int		skip_quotes(char *str, char quote);
int		find_end(char *str, char *possible_sep);
#endif