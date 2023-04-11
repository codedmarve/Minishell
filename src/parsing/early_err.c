
#include "../../includes/minishell.h"

int	early_err(t_data *data)
{
	char *input = data->input;
	if (spaces_err(data->input) == -1)
		return (-1);
	if (quotes_err(input) == -1)
		return (-1);
	if (pipes_err(input) == -1)
		return (-1);
	if (spec_char_err(input) == -1)
		return (-1);
	if (redirection_err(input) == -1)
		return (-1);
	return (0);
}

