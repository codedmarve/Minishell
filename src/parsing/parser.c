

#include "../../includes/minishell.h"

// int expander_needed(char *s)
// {
// 	while (*s)
// 	{
// 		if (*s == '$')
// 		{
// 			return (1);
// 		}
// 		s++;
// 	}
// 	return (0);
// }

// void expander(t_token **token_lst)
// {
// 	t_token *tmp;

// 	tmp = *token_lst;
// 	while (tmp)
// 	{
// 		if (tmp->quote_type == S_Q)
// 		{
// 			tmp = tmp->next;
// 			continue ;
// 		}
// 		if (expander_needed(tmp->string) == 1)
// 		{
// 			printf("expander needed\n");
// 		}
// 		tmp = tmp->next;
// 	}
// }

void	print_after_tokenizer(t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = data->token_lst;
	i = 0;
	while (tmp)
	{
		printf("TOK nr %i: %s TOK_TYPE: %d QUOT: %d\n",
			i, tmp->string, tmp->type, tmp->quote_type);
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

int	parser(t_data *data)
{
	remove_consequtive_quotes(data->input);
	printf("%s\n", data->input);
	tokenizer(&data->token_lst, data->input);
	print_after_tokenizer(data);
	// expander(&data->token_lst);
	return (0);
}
