
#include "../../includes/minishell.h"

t_token	*init_in_quotes(char *s, int *i, char q)
{
	t_token	*token;
	int		len;

	len = skip_quotes(s, q);
	token = ft_calloc(1, sizeof(t_token));
	// if (!token)
	token->string = ft_substr(s, 1, len - 2);
	if (*s == '\'')
		token->quote_type = S_Q;
	else if (*s == '"')
		token->quote_type = D_Q;
	token->type = WORD;
	token->next = NULL;
	*i += len;
	return (token);
}

t_token	*init_pipe_or_sep(char *s, int *i, char p_or_s)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
// 	if (!token)
	token->string = ft_calloc(1, sizeof(char));
// if (!token->string)
//	token->quote_type = NO_Q; // NOT NEEDED sine ft_calloc
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


// <issomefile"/" need be treated as ssomefile/ -> need to remove quotes later
t_token	*init_single_redirection(char *s, int *i, char in_or_out)
{
	t_token	*token;
	int		len;

	*i += skip_spaces(&s[*i + 1]) + 1;
	len = find_end(&s[*i], " <>|");
	token = ft_calloc(sizeof(t_token), 1);
	// if (!token)
	if (s[*i] == '\'')
		token->quote_type = S_Q;
	else if (s[*i] == '"')
		token->quote_type = D_Q;
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
	token = ft_calloc(1, sizeof(t_token));
	// if (!token)
	if (s[*i] == '\'')
		token->quote_type = S_Q;
	else if (s[*i] == '"')
		token->quote_type = D_Q;
	token->string = ft_substr(s, *i, len);
	remove_quotes(token->string);
	token->next = NULL;
	if (in_or_out == '<')
		token->type = HERE_DOC;
	else if (in_or_out == '>')
		token->type = APP_RED;
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
	if (s[*i] == '\'')
		token->quote_type = S_Q;
	else if (s[*i] == '"')
		token->quote_type = D_Q;
	token->string = ft_substr(s, *i, len);
	token->type = WORD;
	token->next = NULL;
	*i += len;
	return (token);
}
