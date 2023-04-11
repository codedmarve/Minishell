/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:37:16 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/04/11 14:45:39 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_envp	t_envp;
typedef struct s_data	t_data;
typedef struct s_token	t_token;

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

void	tokenizer(t_token **token_ll, char *exp);
int parser(t_data *data);


t_token	*init_quotes(char *s, int *i, char q);
t_token	*init_pipe_or_sep(char *s, int *i, char p_or_s);
t_token	*init_single_red(char *s, int *i, char in_or_out);
t_token	*init_double_red(char *s, int *i, char in_or_out);
t_token	*init_word(char *s, int *i);

t_token	*last_token(t_token *list);
void	token_add_back(t_token **list, t_token *new);
void	remove_quotes(char *s);
void	remove_quotes_helper(char *s, char q, int *i, int *j);


int	skip_spaces(char *str);
int	skip_quotes(char *str, char quote);
int	find_end(char *str, char *possible_sep);

#endif