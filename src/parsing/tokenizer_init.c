
#include "../../includes/minishell.h"

t_token	*init_in_quotes(char *s, int *i, char quote)
{
	t_token	*token;
	int		len;

	token = ft_calloc(1, sizeof(t_token));
	// if (!token)
	len = skip_quotes(s, quote);
	token->string = ft_substr(s, 1, len - 2);
	token->type = WORD;
	if (*s == '\'')
		token->quote_type = S_Q;
	else if (*s == '"')
		token->quote_type = D_Q;
	token->next = NULL;
	*i += len;
	return (token);
}

t_token	*init_pipe_or_sep(char *s, int *i, char pipe_or_sep)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
// 	if (!token)
	token->string = ft_calloc(1, sizeof(char));
// if (!token->string)
//	token->quote_type = NO_Q; // NOT NEEDED since ft_calloc
	if (pipe_or_sep == ' ')
	{
		*i += skip_spaces(s);
		token->type = SEP; // not needed since ft_calloc
	}
	else
	{
		*i = *i + 1;
		token->type = PIPE;
	}
	token->next = NULL;
	return (token);
}

/*
<issomefile"/" need be treated as ssomefile/ -> need to remove quotes later
*/
t_token	*init_single_redirection(char *s, int *i, char in_or_out)
{
	t_token	*token;
	int		len;

	token = ft_calloc(sizeof(t_token), 1);
	// if (!token)
	*i += skip_spaces(&s[*i + 1]) + 1;
	len = find_end(&s[*i], " <>|");
	token->string = ft_substr(s, *i, len);
	remove_quotes(token->string);
	if (in_or_out == '<')
		token->type = IN_RED;
	else if (in_or_out == '>')
		token->type = OUT_RED;
	if (s[*i] == '\'')
		token->quote_type = S_Q;
	else if (s[*i] == '"')
		token->quote_type = D_Q;
	token->next = NULL;
	*i += len;
	return (token);
}

t_token	*init_double_redirection(char *s, int *i, char in_or_out)
{
	t_token	*token;
	int		len;

	token = ft_calloc(1, sizeof(t_token));
	// if (!token)
	*i += skip_spaces(&s[*i + 2]) + 2;
	len = find_end(&s[*i], " <>|");
	token->string = ft_substr(s, *i, len);
	remove_quotes(token->string);
	if (in_or_out == '<')
		token->type = HERE_DOC;
	else if (in_or_out == '>')
		token->type = APP_RED;
	if (s[*i] == '\'')
		token->quote_type = S_Q;
	else if (s[*i] == '"')
		token->quote_type = D_Q;
	token->next = NULL;
	*i += len;
	return (token);
}

t_token	*init_word(char *s, int *i)
{
	t_token	*token;
	int		len;

	len = find_end(&s[*i], " '\"<>|");
	token = ft_calloc(1, sizeof(t_token));
	// if (!token)
	token->string = ft_substr(s, *i, len);
	token->type = WORD;
	if (s[*i] == '\'')
		token->quote_type = S_Q;
	else if (s[*i] == '"')
		token->quote_type = D_Q;
	token->next = NULL;
	*i += len;
	return (token);
}
