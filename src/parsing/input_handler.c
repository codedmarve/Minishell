
#include "../../includes/minishell.h"
// #include "../../includes/parsing.h"



int input_handler(t_data *data)
{
	char *input = data->input;

	manipulate_input(&input);
	early_err(data); // returns positive value if error found



	printf("pipe groups: %d\n", str_counter(input, '|'));

	data->input_pipe_groups = minishell_split(input, '|');
	int i = 0;
	while (data->input_pipe_groups[i])
	{
		printf("group nr %d: %s\n", i, data->input_pipe_groups[i]);
		i++;
	}
	return (0);
}
