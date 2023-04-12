
#include "../../includes/minishell.h"

int	redirection_err_s_in(char *s, int *i)
{
	*i += skip_spaces(&s[*i + 1]) + 1;
	if (s[*i] == '\0' || s[*i] == '|' || s[*i] == '>' || s[*i] == '<')
	{
		return (printf("minishell: token error: `<'\n"), -1);
	}
	return (*i);
}

int	redirection_err_s_out(char *s, int *i)
{
	*i += skip_spaces(&s[*i + 1]) + 1;
	if (s[*i] == '\0' || s[*i] == '|' || s[*i] == '>' || s[*i] == '<')
	{
		return (printf("minishell: token error: `>'\n"), -1);
	}
	return (*i);
}

int	redirection_err_d_in(char *s, int *i)
{
	*i += skip_spaces(&s[*i + 2]) + 2;
	if (s[*i] == '\0' || s[*i] == '|' || s[*i] == '>' || s[*i] == '<')
	{		
		return (printf("minishell: token error: `<<'\n"), -1);
	}
	return (*i);
}

int	redirection_err_d_out(char *s, int *i)
{
	*i += skip_spaces(&s[*i + 2]) + 2;
	if (s[*i] == '\0' || s[*i] == '|' || s[*i] == '>' || s[*i] == '<')
	{
		return (printf("minishell: token error: `>>'\n"), -1);
	}
	return (*i);
}