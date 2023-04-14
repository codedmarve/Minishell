
#include "../../includes/minishell.h"

void	print_after_tokenizer(t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = data->token_lst;
	i = 0;
	while (tmp)
	{
		printf("TOK %i:%s TOK_TYPE:%d QUOT:%d\n",
			i, tmp->string, tmp->type, tmp->quote_type);
		i++;
		tmp = tmp->next;
	}
}

void	print_after_expansion(t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = data->token_lst;
	i = 0;
	while (tmp)
	{
		printf("TOK %i EXP:%s\n", i, tmp->string);
		i++;
		tmp = tmp->next;
	}
}

/// @brief modifies input string, 
/// skips consecutive quotes that are not inside other quotes
/// for example:
/// $''USER becomes $USER 
/// hi""bye becomes hibye
/// doesnt affect consecutive quotes inside other quotes:
/// "    '' " will remain unchanged
/// @param input
void	remove_consequtive_quotes(char *input)
{
	int	i;
	int	j;
	int	in_q;

	i = 0;
	j = 0;
	in_q = 0;
	while (input[i] != '\0')
	{
		if (!in_q && ((input[i] == '"' && input[i + 1] == '"')
				|| (input[i] == '\'' && input[i + 1] == '\'')))
            i += 2;
		else
		{
			if (input[i] == '"' || input[i] == '\'')
				in_q = !in_q;
			input[j] = input[i];
			i++;
			j++;
		}
	}
	input[j] = '\0';
}

/// @brief checks if string contains $ char
/// @param s 
/// @return 1 if $ found
int dollar_in_str(char *s)
{
	while (*s)
	{
		if (*s == '$')
			return (1);
		s++;
	}
	return (0);
}

/// @brief cheks if current char can belong to env varialbe
/// @param c 
/// @return 
int	env_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

/// @brief takes exit status from global variable,
/// saves it i a string *value
/// @param  
/// @return *value
char	*exit_status(void)
{
	char	*value;

	value = ft_itoa(g_exit_status);
	if (!value)
		return (NULL);
	return (value);
}

void expand_token(char *input) 
{
	return ;
}

// void expand_token_lst(t_token *token_lst) {
//     t_token *current_token = token_lst;

//     while (current_token != NULL) {
//         char *expanded_string = expand_token(current_token->string);
//         free(current_token->string);
//         current_token->string = expanded_string;

//         current_token = current_token->next;
//     }
// }

void	expand_token_lst(t_token *token_lst)
{
	t_token	*tmp;

	tmp = token_lst;
	while (tmp != NULL)
	{
		if (tmp->quote_type != S_Q && dollar_in_str(tmp->string))
			expand_token(tmp->string);
		tmp = tmp->next;
	}
}

int	parser(t_data *data)
{
	remove_consequtive_quotes(data->input);
	printf("%s\n", data->input);
	tokenizer(&data->token_lst, data->input);
	print_after_tokenizer(data);
	expand_token_lst(data->token_lst);
	print_after_expansion(data);
	return (0);
}
