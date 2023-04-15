
#include "../../includes/minishell.h"

/// @brief no lexing happens in case of error
/// CHECK BEHAVIOR OF BASH REDIRECT AGAIN!!!
/// @param data 
/// @return -1 on error
int	early_err(t_data *data)
{
	char	*input;

	input = data->input;
	if ((spaces_err(input) == -1)
		|| (quotes_err(input) == -1)
		|| (pipes_err(input) == -1)
		|| (spec_char_err(input) == -1)
		|| (redirection_err(input) == -1))
		return (-1);
	return (0);
}
