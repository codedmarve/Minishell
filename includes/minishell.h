
#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>

# include "../library/libft/libft.h"

int	exit_status;

// typedef struct s_envp
// {
// 	char			*envp_key;
// 	char			*envp_value;
// 	struct s_envp	*next;
// }					t_envp;

typedef struct s_token
{
	char			*string;
	int				type;
	int				quote_type;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	char	*input;
	t_token *token_lst;
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
void	tokenizer(t_token **token_lst, char *input);

// tokenizer_init.c
t_token	*init_in_quotes(char *s, int *i, char quote);
t_token	*init_pipe_or_sep(char *s, int *i, char pipe_or_sep);
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