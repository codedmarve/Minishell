

#include "../../includes/minishell.h"

int	spaces_err(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '\0')
		return (-1);
	else
		return (0);
}

int	quotes_err(char *s)
{
	int	dq_open;
	int	sq_open;
	int	i;

	i = 0;
	dq_open = 0;
	sq_open = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && !dq_open && !sq_open)
			sq_open = 1;
		else if (s[i] == '"' && !dq_open && !sq_open)
			dq_open = 1;
		else if (s[i] == '\'' && !dq_open && sq_open)
			sq_open = 0;
		else if (s[i] == '"' && dq_open && !sq_open)
			dq_open = 0;
		i++;
	}
	if (dq_open || sq_open)
		return (printf("minishell: unsupported open quotes\n"), -1);
	return (0);
}

int	pipes_err(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '|')
		return (printf("minishell: token error: `|'\n"), -1);
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			i += skip_quotes(&input[i], '\'');
		else if (input[i] == '"')
			i += skip_quotes(&input[i], '"');
		else if (input[i] == '|')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '|' || input[i] == '\0')
				return (printf("minishell: token error: `|'\n"), -1);
		}
		else
			i++;
	}
	return (0);
}

int	spec_char_err(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			i += skip_quotes(&input[i], '\'');
		else if (input[i] == '"')
			i += skip_quotes(&input[i], '"');
		else if (input[i] == ';' || input[i] == '&'
			|| input[i] == '\\' || input[i] == '*'
			|| input[i] == '~' || input[i] == '%'
			|| input[i] == '#')
		{
			return (printf("minishell: unsupported special char\n"), -1);
		}
		else
			i++;
	}
	return (0);
}

int	redirection_err(char *input)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	while (input[i] != '\0' && value != -1)
	{
		if (input[i] == '\'')
			i += skip_quotes(&input[i], '\'');
		else if (input[i] == '"')
			i += skip_quotes(&input[i], '"');
		else if (input[i] == '<' && input[i + 1] != '<')
			value = redirection_err_s_in(input, &i);
		else if (input[i] == '>' && input[i + 1] != '>')
			value = redirection_err_s_out(input, &i);
		else if (input[i] == '<' && input[i + 1] == '<')
			value = redirection_err_d_in(input, &i);
		else if (input[i] == '>' && input[i + 1] == '>')
			value = redirection_err_d_out(input, &i);
		else
			i++;
	}
	if (value == -1)
		return (-1);
	return (0);
}
