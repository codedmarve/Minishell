
#include "../../includes/minishell.h"

#define QUOTES_ERR

bool	is_whitespace_char(char c)
{
	return (ft_strchr(" \f\n\t\r\v", c));
}

bool	is_quotation_char(char c)
{
	return (c == '\"' || c == '\'');
}

/*
pipe operator:
passes the output of one command as input to another

redirection operators:
token that performs a redirection function
*/
bool	is_operator_char(char c)
{
	return (ft_strchr("><|", c));
}

/*
metachar: when unquoted, separates words. 
A metacharacter is a space, tab, newline, 
or one of the following characters: 
‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.
*/
bool	is_metachar(char c)
{
	return (is_whitespace_char(c) || is_operator_char(c));
}

// int	get_chartype(char c)
// {
// 	if (p->double_quoted || p->single_quoted)
// 		return (word);
// 	if (c == '|')
// 		return (pipe_char);
// 	if (is_whitespace(c))
// 		return (whitespace);
// 	if (is_operatorchar(c))
// 		return (operator);
// 	else
// 		return (word);
// }

// typedef enum char_type
// {
// 	init_lex = 1,
// 	word = 2,
// 	whitespace = 4,
// 	operator = 8,
// 	pipe_char = 16,
// }	t_chartype;

// typedef enum token_type
// {
// 	init_tok = 1,
// 	newcmd = 2,
// 	input_redir,
// 	output_redir_oper = 8,
// 	input_redir_str = 16,
// 	output_redir_str = 32,
// 	pipe_oper = 64,
// 	cmdstring = 128
// }	t_toktype;

/*********************************************************************************************/
bool	open_quotes_found(char *s) //NORM FIX
{
	bool	dq_open;
	bool	sq_open;
	int		i;

	i = 0;
	dq_open = false;
	sq_open = false;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && !dq_open && !sq_open)
			sq_open = true;
		else if (s[i] == '\'' && !dq_open && sq_open)
			sq_open = false;
		else if (s[i] == '"' && !dq_open && !sq_open)
			dq_open = true;
		else if (s[i] == '"' && dq_open && !sq_open)
			dq_open = false;
		i++;
	}
	if (dq_open || sq_open)
		return (true);
	return (false);
}

bool opening_pipe_err(char *input)
{
	if (input[0] == '|')
		return (true);
	return (false);
}

bool newline_err(char *input)
{
	if (input[ft_strlen(input) - 1] == '<' 
		|| input[ft_strlen(input) - 1] == '>'
		|| input[ft_strlen(input) - 1] == '|') // not really bash - last PIPE is waiting for input) 
		return (true);
	return (false);
}

void remove_surrounding_whitespaces(char *input)
{
	input = ft_strtrim(input, " \f\n\t\r\v"); //remove start/end spaces, do we neeed empty string check here?
	// printf("START%sEND\n", data->input);
}

/*
early error check:

0. getting rid of white spaces at the beginning/end of string
1. quotes must be closed -> minishell: unsupported open quotes
2. first char may not be a pipe -> minishell: syntax error near unexpected token `|'
3. last char may not be an operator (since it' s not 100% bash, it also doesn't support PIPE
as a last char)

remaining syntax check is performed after tokenization, makes it easier
*/
bool early_err(char *input)
{
	remove_surrounding_whitespaces(input);
	if (open_quotes_found(input))
		return (printf("minishell: unsupported open quotes\n"), true);
	if (opening_pipe_err(input))
		return (printf("minishell: syntax error near unexpected token `|'\n"), true);
	if (newline_err(input))
		return (printf("minishell: syntax error near unexpected token `newline'\n"), true);
	return (false);
}
/*********************************************************************************************/

int input_handler(t_data *data, char *input)
{
	(void)input;
	early_err(data->input); // if errror??
	// lexer(data);
	return (0);
}
