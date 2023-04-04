
#include "../../includes/minishell.h"
// #include "../../includes/parsing.h"


void	manipulate_input(char **input)
{
	unify_spaces(input);
	remove_extra_spaces(input);
}

void	manipulate_input2(char **input)
{
	attach_redirect(input);
	add_space_before_redirect(input);
	// printf("cleaned input: START%sEND\n", *input);
}

int input_handler(t_data *data)
{
	char *input = data->input;

	manipulate_input(&input);
	manipulate_input2(&input);
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
