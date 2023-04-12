
#include "../../includes/minishell.h"

// void clean_up(t_data *data)
// {

// }

int input_handler(t_data *data)
{
	if (early_err(data) == -1) // CHANGE TO -1 for error EVERYWHERE
		return (-1);
	if (parser(data) == -1)
		return (-1);
	// clean_up(data);
	return (0);
}
