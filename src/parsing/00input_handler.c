
#include "../../includes/minishell.h"


int input_handler(t_data *data)
{
	if (early_err(data) == -1)
		return (-1);
	if (parser(data) == -1)
		return (-1);
	return (0);
}
