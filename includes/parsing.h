/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:37:16 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/04/04 00:53:54 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_envp t_envp;
typedef struct s_data t_data;

//early_err.c
int	opening_pipe_err(char *input);
int	newline_err(char *input);
int early_err(t_data *data);

//unsupported_err.c
int	unsupported_quotes_err(char *s);
int	unsupported_char_err(char *input);
int	unsupported_pipe_err(char *input);
int	unsupported_redir_err(char *input, char c);

//input_handler.c
int input_handler(t_data *data);

//manipulate input
static int	ft_isspace(char c);
void	unify_spaces(char **input);
void	remove_extra_spaces(char **input);
void manipulate_input(char **input);

//quotes_utils
int	quotes_are_closed(char c);
void	quotes_default(void);

// modified split
char	**shell_split(char *input, char delimiter);
int	str_counter(char *input, char delimiter);
char	*init_str(char *input, char delimiter);
char **shell_split_remove_spaces(char *input);
#endif