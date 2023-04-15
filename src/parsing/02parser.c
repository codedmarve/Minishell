
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
		printf("%s ", tmp->string);
		i++;
		tmp = tmp->next;
	}
	printf("\n");
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
	tokenizer(&data->token_lst, data->input);
	print_after_tokenizer(data);
	expand_token_lst(&data->token_lst);
	print_after_expansion(data);
	// if (parser_err == -1) // checks if redirect (and what else?) are OK
	
	return (0);
}
