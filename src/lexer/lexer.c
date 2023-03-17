
#include "../../includes/minishell.h"

// int	only_spaces(char *s)
// {
// 	int	i;
// 	i = 0;
// 	while (s[i] == ' ')
// 		i++;
// 	if (s[i] == '\0')
// 		return (-1);
// 	else
// 		return (0);
// }

/*
bash-3.2$ ls &&&
bash: syntax error near unexpected token `&'
SIC! COPY QUOTATION EXACTLY!
*/
int	lexer_err(char *token)
{
	ft_printf("minishell: syntax error near unexpected token %s\n", token);
	return (-1);
}

// int	skip_spaces(char *s)
// {
// 	int	i;
// 	i = 0;
// 	while (s[i] == ' ')
// 		i++;
// 	return (i);
// }
