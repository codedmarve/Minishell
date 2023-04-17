/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:46:58 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/04/12 23:46:58 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>

# include "../library/libft/libft.h"

#define MAX_TOKEN_SIZE 1024
int		g_exit_status;

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
	int				quote_type;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	// typedef struct s_cmd *cmd_head;
	int cmd_idx;
	char **cmd_splitted;
	// char *cmd_path;
	int fd_infile;
	int fd_outfile;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_data
{
	char	*input;
	t_token	*token_lst;
	t_envp	*env_lst;
	t_cmd 	*cmd_lst;
}	t_data;

enum	e_quote_types
{
	NO_Q,
	S_Q,
	D_Q,
};

enum	e_token_types
{
	SEP,
	WORD,
	PIPE,
	IN_RED,
	OUT_RED,
	HERE_DOC,
	APP_RED,
};

// envplist_handler.c
void	envplist_handler(t_envp **head, char **envp);
t_envp	*create_envp_node(char **data);
void	envp_add_back(t_envp **lst, t_envp *new);
t_envp	*envp_last(t_envp *lst);

// envplist_utils.c
char	*ft_strdup2(const char *str, int len);
char	*ft_strdup1(const char *str);
void	print_env(t_data *data);

// main.c
int		main(int ac, char **av, char **envp);

// 00input_handler.c
int		input_handler(t_data *data);

// 01early_err.c
int		early_err(t_data *data);

// 01early_err_utils.c
int		pipes_err(char *input);
int		spaces_err(char *input);
int		quotes_err(char *s);
int		spec_char_err(char *input);
int		redirection_err(char *input);

// 01early_err_utils2.c
int		redirection_err_s_in(char *s, int *i);
int		redirection_err_s_out(char *s, int *i);
int		redirection_err_d_in(char *s, int *i);
int		redirection_err_d_out(char *s, int *i);

// 02parser.c
void	remove_consequtive_quotes(char *input);
void	free_token_lst(t_token **token_lst);
int		parser(t_data *data);

// 03tokenizer.c
void	tokenizer(t_token **token_lst, char *input);

// 03tokenizer_init.c
t_token	*init_in_quotes(char *s, int *i, char quote);
t_token	*init_pipe_or_sep(char *s, int *i, char pipe_or_sep);
t_token	*init_single_redirection(char *s, int *i, char in_or_out);
t_token	*init_double_redirection(char *s, int *i, char in_or_out);
t_token	*init_word(char *s, int *i);

// 03tokenizer_utils.c
t_token	*token_last(t_token *lst);
void	token_add_back(t_token **lst, t_token *new);
void	remove_quotes(char *s);

// 04expander.c
char	*expand_token(char *token);
void	expand_token_lst(t_token **token_lst);

// 04expander2.c
void	init_exit_status(char **new_ptr, int *j_ptr, int *i_ptr);
void	init_single_dollar(char **new_ptr, int *j_ptr, int *i_ptr);
void	expand_remainder(char **new_ptr, int *j_ptr, int *i_ptr, char *token);
void	init_env_var(char **new_ptr, int *j_ptr, int *i_ptr, char *token);
void	copy_token_char(char **new_ptr, int *j_ptr, char c);

// 04expander_utils.c
int		dollar_in_str(char *s);
char	*get_exit_status(void);

// 05redirect_handler.c
void	close_files_if_open(int *fd_infile, int *fd_outfile);
int		init_in_red(int *fd_infile, char *filename);
int		init_out_red(int *fd_outfile, char *filename);
int		init_app_red(int *fd_outfile, char *filename);
// int	init_here_doc(int *fd_outfile, char *filename);
int		redirect_handler(t_token **token_lst);

// 06interpreter.c
int	interpreter(t_data *data);

// utils.c
int		skip_spaces(char *str);
int		skip_quotes(char *str, char quote);
int		find_end(char *str, char *possible_sep);

#endif