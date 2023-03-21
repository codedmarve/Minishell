#include "../../includes/minishell.h"

/*
add_history() from readline library saves command history
no extra actions needed

with readline we can read a line from the terminal (similar to scanf)
-> https://de.wikipedia.org/wiki/GNU_readline
readline function mallocs -> needs to get freed in the end
flag to compile readline correctly: -lreadline

functions we can use:
rl_clear_history
*/

// char	*get_prompt(void)
// {
// 	char	*input;

// 	input = readline("minishell$ ");
// 	if (ft_strlen(input) > 0)
// 	{
// 		// printf("%s\n", input); 
// 		add_history(input); // create history
// 	}
// 	return (input);
// }
