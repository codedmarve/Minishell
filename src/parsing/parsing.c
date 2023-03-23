
#include "../../includes/minishell.h"

// int	all_quotes_closed(char *str)
// {
// 	int d_quotes_open;
// 	int s_quotes_open;
// 	int i;

// 	d_quotes_open = 0;
// 	s_quotes_open = 0;
// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] == '\'' && !d_quotes_open)
// 		{
// 			if (s_quotes_open)
// 				s_quotes_open = 0;
// 			else
// 				s_quotes_open = 1;
// 		}
// 		else if (str[i] == '\"' && !s_quotes_open)
// 		{
// 			if (d_quotes_open)
// 				d_quotes_open = 0;
// 			else
// 				d_quotes_open = 1;
// 		}
// 	}
// 	if (!d_quotes_open && !s_quotes_open)
// 		return (1);
// 	return (0);
// }

typedef struct s_quotation
{
	int d_quotes_open;
	int s_quotes_open;
	int i;
} t_quotation;

int	all_quotes_closed(char *str) // NORM FIX
{
	t_quotation q;

	q.d_quotes_open = 0;
	q.s_quotes_open = 0;
	q.i = -1;
	while (str[++q.i])
	{
		if (str[q.i] == '\'' && !q.d_quotes_open) // encounter ', not inside "...
		{ // inside other qoutation will be ignored
			if (q.s_quotes_open) // was ' single before
				q.s_quotes_open = 0;
			else
				q.s_quotes_open = 1;
		}
		else if (str[q.i] == '\"' && !q.s_quotes_open)
		{
			if (q.d_quotes_open)
				q.d_quotes_open = 0;
			else
				q.d_quotes_open = 1;
		}
	}
	if (!q.d_quotes_open && !q.s_quotes_open)
		return (1);
	return (0);
}

int input_handler(char *input)
{
	if (!all_quotes_closed(input))
		printf("close quotes!\n");
	return (0);
}