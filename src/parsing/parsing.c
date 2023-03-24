
#include "../../includes/minishell.h"

bool	is_whitespace_char(char c)
{
	return (ft_strchr(" \f\n\t\r\v", c));
}

bool is_pipe_char(char c)
{
	return (c == '|');
}

bool is_redirection_char(char c)
{
	return(ft_strchr("><", c));
}

bool	is_quotation_char(char c)
{
	return (c == '\"' || c == '\'');
}

bool is_operator_char(char c)
{
	return (ft_strchr("><|", c));
}

bool	is_metachar(char c)
{
	return (is_whitespace_char(c) || is_operator_char(c));
}

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

void remove_leading_whitespaces(char *input)
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
*/
bool early_err(char *input)
{
	remove_leading_whitespaces(input);
	if (open_quotes_found(input))
		return (printf("minishell: unsupported open quotes\n"), true);
	if (opening_pipe_err(input))
		return (printf("minishell: syntax error near unexpected token `|'\n"), true);
	if (newline_err(input))
		return (printf ("minishell: syntax error near unexpected token `newline'\n"), true);
	return (false);
}
/*********************************************************************************************/

int input_handler(t_data *data, char *input)
{
	early_err(input); // if
	return (0);
}
