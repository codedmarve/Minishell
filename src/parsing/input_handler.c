
#include "../../includes/minishell.h"
// #include "../../includes/parsing.h"



int input_handler(t_data *data)
{
	char *input = data->input;

	manipulate_input(&input);
	early_err(data); // returns positive value if error found



	data->input_strings = shell_split_remove_spaces(input);
	int i = 0;
	while (data->input_strings[i])
	{
		printf("string nr %d: %s\n", i, data->input_strings[i]);
		i++;
	}
	return (0);
}
