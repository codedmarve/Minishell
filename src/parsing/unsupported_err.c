
#include "../../includes/minishell.h"
// #include "../../includes/parsing.h"

/*
function checks if there are open quotes found,
" ' " ' " will be treated as an error, " ' " ' " ' - not
*/
int	unsupported_quotes_err(char *s)
{
	int	dq_open;
	int	sq_open;
	int		i;

	i = 0;
	dq_open = 0;
	sq_open = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && !dq_open && !sq_open)
			sq_open = 1;
		else if (s[i] == '\'' && !dq_open && sq_open)
			sq_open = 0;
		else if (s[i] == '"' && !dq_open && !sq_open)
			dq_open = 1;
		else if (s[i] == '"' && dq_open && !sq_open)
			dq_open = 0;
		i++;
	}
	if (dq_open || sq_open)
		return (-1);
	return (0);
}

/*
our minishell shouldn't support special chars as ; & \
according to the subject,
so we immideately take care of that

(they are ofc allowed as part of a string in quotation)
*/
int	unsupported_char_err(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (!quotes_are_closed(input[i]))
		{
			i++;
			continue ;
		}
		if (input[i] == ';' || input[i] == '&'
			|| input[i] == '\\')
		{
			quotes_default();
			return (1);
		}
		i++;
	}
	quotes_default();
	return (0);
}

/*
our minishell should support single pipes only
(double pipes are ofc allowed as part of a string
in quotation)
*/
int	unsupported_pipe_err(char *input)
{
	int		i;

	i = 0;
	while (input[i + 1])
	{
		if (!quotes_are_closed(input[i]))
		{
			i++;
			continue ;
		}
		if (input[i] == '|' && input[i + 1] == '|')
		{
			quotes_default();
			return (1);
		}
		i++;
	}
	quotes_default();
	return (0);
}

/*
minishell supports only < >> << >

other sombination are allowed as a part of quoted string
*/
int	unsupported_redir_err(char *input, char c)
{
	int		i;

	i = 0;
	while (input[i] && input[i + 1] && input[i + 2])
	{
		if (!quotes_are_closed(input[i]))
		{
			i++;
			continue ;
		}
		if (input[i] == c
			&& input[i] == input[i + 1]
			&& input[i] == input[i + 2])
			return (1);
		i++;
	}
	quotes_default();
	return (0);
}

/*
operators in minishell:
< > << >> |
allowed combos in bash:
<<< (herestring, but not allowed in minishell subject)
| <
| >
| >>
| <<
not allowed
<		>		<<		>>		|
______________________________________
< <		> <		<< <	>> <	| |
< >		> >		<< >	>> >
< <<	> <<	<< <<	>> <<
< >>	> >>	<< >>	>> >>
< |		> |		<< |	>> |
______________________________________
*/