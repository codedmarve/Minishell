
#include "../../includes/minishell.h"

/// @brief takes a pointer to a string as input
/// and checks if the string contains only spaces.
/// @param input 
/// @return -1 if contains only spaces
int	spaces_err(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '\0')
		return (-1);
	return (0);
}

/// @brief checks for mismatched quotes in the input string.
/// It takes a pointer to a character array as input and returns an int value.
///
/// The function initializes two variables, dq_open and sq_open, to 0,
/// representing whether a double quote or single quote is currently open.
/// It then iterates through each character of the input string s.
///
/// If it encounters a single quote or double quote and that type of quote
/// is not currently open, it sets the appropriate variable to 1.
///
/// If it encounters a single quote or double quote and the appropriate type
/// of quote is already open, it sets the appropriate variable to 0
/// to close the quote.
///
/// If at the end of the loop either of the dq_open or sq_open variables 
// is still set to 1, it means that there is a mismatched quote, 
/// and the function returns -1 and prints an error message.
/// 
/// Otherwise, the function returns 0 to indicate that there are no errors.
/// @param s 
/// @return 
int	quotes_err(char *s)
{
	int	dq_open;
	int	sq_open;
	int	i;

	i = 0;
	dq_open = 0;
	sq_open = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && !dq_open && !sq_open)
			sq_open = 1;
		else if (s[i] == '"' && !dq_open && !sq_open)
			dq_open = 1;
		else if (s[i] == '\'' && !dq_open && sq_open)
			sq_open = 0;
		else if (s[i] == '"' && dq_open && !sq_open)
			dq_open = 0;
		i++;
	}
	if (dq_open || sq_open)
		return (printf("minishell: unsupported open quotes\n"), -1);
	return (0);
}

/// @brief checks if there are any errors related to pipes in the input command.
///
/// It starts by skipping any leading spaces in the input.
/// If the first character encountered is a pipe, 
/// it indicates a token error and the function returns -1 after printing
/// an appropriate error message.
///
/// Then it iterates through the input character by character.
/// If it encounters a single or double quote, 
/// it skips the quoted string to avoid considering pipes inside quotes.
///
/// If it encounters a pipe char, it skips any subsequent spaces and checks 
/// if the next character is another pipe or if it is the end of the input. 
///
/// In either case, it indicates a token error and the function returns -1 
/// after printing an appropriate error message.
///
/// If it reaches the end of the input without encountering any errors,
/// it returns 0 to indicate success.
/// @param input 
/// @return 
int	pipes_err(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '|')
		return (printf("minishell: token error: `|'\n"), -1);
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			i += skip_quotes(&input[i], '\'');
		else if (input[i] == '"')
			i += skip_quotes(&input[i], '"');
		else if (input[i] == '|')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '|' || input[i] == '\0')
				return (printf("minishell: token error: `|'\n"), -1);
		}
		else
			i++;
	}
	return (0);
}

/// @brief minishell supports limited amt of special chars outside quotes:
/// pipe, and redirections.
/// couldn't add # ‘ ´ here
/// @param input 
/// @return -1 on error
int	spec_char_err(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			i += skip_quotes(&input[i], '\'');
		else if (input[i] == '"')
			i += skip_quotes(&input[i], '"');
		else if (input[i] == ';' || input[i] == '&'
			|| input[i] == '\\' || input[i] == '*'
			|| input[i] == '~' || input[i] == '%'
			|| input[i] == '(' || input[i] == ')'
			|| input[i] == '[' || input[i] == ']'
			|| input[i] == '{' || input[i] == '}'
			|| input[i] == '^' || input[i] == '`')
		{
			return (printf("minishell: unsupported special char\n"), -1);
		}
		else
			i++;
	}
	return (0);
}

/// @brief minishell supports > >> < << only, 
/// no redirection on the end of input, 
/// no redirection before pipe
/// @param input 
/// @return -1 on error
int	redirection_err(char *input)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	while (input[i] != '\0' && value != -1)
	{
		if (input[i] == '\'')
			i += skip_quotes(&input[i], '\'');
		else if (input[i] == '"')
			i += skip_quotes(&input[i], '"');
		else if (input[i] == '<' && input[i + 1] != '<')
			value = redirection_err_s_in(input, &i);
		else if (input[i] == '>' && input[i + 1] != '>')
			value = redirection_err_s_out(input, &i);
		else if (input[i] == '<' && input[i + 1] == '<')
			value = redirection_err_d_in(input, &i);
		else if (input[i] == '>' && input[i + 1] == '>')
			value = redirection_err_d_out(input, &i);
		else
			i++;
	}
	if (value == -1)
		return (-1);
	return (0);
}
