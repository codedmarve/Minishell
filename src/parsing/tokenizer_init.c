#include "../../includes/minishell.h"

t_token	*init_in_quotes(char *s, int *i, char q)
{
	t_token	*token;
	int		len;

	len = skip_quotes(s, q);
	token = malloc(sizeof(t_token));
	// if (!token)
	// {
	// 	//
	// 	return (NULL);
	// }
	token->string = ft_substr(s, 1, len - 2);
	token->type = WORD;
	token->next = NULL;
	*i += len;
	return (token);
}

t_token	*init_pipe_or_sep(char *s, int *i, char p_or_s)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
// 	if (!token)
	token->string = malloc(sizeof(char));
	// if (!token->string)
	token->string[0] = '\0';
	token->next = NULL;
	if (p_or_s == ' ')
	{
		*i += skip_spaces(s);
		token->type = SEP;
	}
	else
	{
		*i = *i + 1;
		token->type = PIPE;
	}
	return (token);
}

t_token	*init_single_redirection(char *s, int *i, char in_or_out)
{
	t_token	*token;
	int		len;

	*i += skip_spaces(&s[*i + 1]) + 1;
	len = find_end(&s[*i], " <>|");
	token = malloc(sizeof(t_token));
	// if (!token)
	// {
	// 	//
	// 	return (NULL);
	// }
	token->string = ft_substr(s, *i, len);
	remove_quotes(token->string);
	token->next = NULL;
	if (in_or_out == '<')
		token->type = IN_RED;
	else if (in_or_out == '>')
		token->type = OUT_RED;
	*i += len;
	return (token);
}

t_token	*init_double_redirection(char *s, int *i, char in_or_out)
{
	t_token	*token;
	int		len;

	*i += skip_spaces(&s[*i + 2]) + 2;
	len = find_end(&s[*i], " <>|");
	token = malloc(sizeof(t_token));
	// if (!token)
	// {
	// 	//
	// 	return (NULL);
	// }
	token->string = ft_substr(s, *i, len);
	remove_quotes(token->string);
	token->next = NULL;
	if (in_or_out == '<')
		token->type = HERE_DOC;
	else if (in_or_out == '>')
		token->type = APPEND_RED;
	*i += len;
	return (token);
}

t_token	*init_word(char *s, int *i)
{
	t_token	*token;
	int		len;

	len = find_end(&s[*i], " '\"<>|");
	token = malloc(sizeof(t_token));
	// if (!token)
	// {
	// 	//
	// 	return (NULL);
	// }
	token->string = ft_substr(s, *i, len);
	token->type = WORD;
	token->next = NULL;
	*i += len;
	return (token);
}