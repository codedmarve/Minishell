

#include "../../includes/minishell.h"

// /* checker if currently quotes are open
// gets called in a loop
// returns (0) if the quotes are not closed
// */

// int	quotes_are_closed(char c)
// {
// 	static int	dq_open = 0;
// 	static int	sq_open = 0;

// 	if (c == '\'' && !dq_open && sq_open)
// 		sq_open = 0;
// 	else if (c == '\'' && !dq_open && !sq_open)
// 		sq_open = 1;
// 	else if (c == '\"' && !sq_open && dq_open)
// 		dq_open = 0;
// 	else if (c == '\"' && !sq_open && !dq_open)
// 		dq_open = 1;
// 	if (!dq_open && !sq_open)
// 		return (1);
// 	return (0);
// }

// /*
// sets the static variables 
// inside the functions to their default val
// */
// void	quotes_default(void)
// {
// 	if (quotes_are_closed('\'') == 0)
// 		quotes_are_closed('\'');
// 	if (quotes_are_closed('\"') == 0)
// 		quotes_are_closed('\"');
// }
