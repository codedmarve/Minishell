#include "../../includes/minishell.h"
// #include "../../includes/parsing.h"


void	manipulate_input(char **input)
{
	unify_spaces(input);
	remove_extra_spaces(input);
	printf("cleaned input: %s\n", *input);
}


int input_handler(t_data *data)
{

	if (early_err(data)) // CHANGE TO -1 for error EVERYWHERE
		return (-1);
	//// didnt change anything, why segfault if remove eatly error??
	printf("%s\n", data->input);
	if (parser(data) == -1)
		return (-1);
	// data->input_strings = shell_split_remove_spaces(input);
	// int	i = 0;
	// while (data->input_strings[i])
	// 	{
	// 		printf("substr idx: %d, str: %s\n", i, data->input_strings[i]);
	// 		i++;
	// 	}
	return (0);
}
