
#include "../../includes/minishell.h"


int input_handler(t_data *data)
{
	if (!ft_strncmp(data->input, "exit", 4) && ft_strlen(data->input) == 4)
		exit_free(data);
	if (early_err(data) == -1)
		return (-1);
	if (parser(data) == -1)
		return (-1);
	cmd_init(data);
	get_cmdpath(data);
	init_fds(data);
	execute(data);
	exec_free(data);
	return (0);
}
