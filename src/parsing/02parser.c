
#include "../../includes/minishell.h"

void	print_full_token_data(t_data *data)
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

void	print_token_string(t_data *data)
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

/// @brief takes a pointer to a string input and removes consecutive quotes
/// of the same type (either single or double quotes) from it.
///nIt does this by iterating through the string character by character,
/// keeping track of whether it is currently inside a quoted section or not.
/// 
/// If it encounters two consecutive quotes of the same type (i.e. " " or ' '),
/// it skips the second quote and continues iterating.
///
/// If it encounters a quote that starts a new quoted section,
/// it toggles the in_q variable accordingly.
///
/// After iterating through the entire string,
/// it writes a null character '\0' at the end to terminate the resulting str.
///
/// Note that this function modifies the input string in place,
/// so any changes made to input inside this function will be reflected
/// in the original variable that was passed in:
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

void	free_token_lst(t_token **token_lst)
{
	t_token	*tmp;

	tmp = *token_lst;
	while (*token_lst != NULL)
	{
		if (tmp->string)
			free(tmp->string);
		tmp = tmp->next;
		free(*token_lst);
		*token_lst = tmp;
	} // free(token_lst) here???
}

int	parser(t_data *data)
{
	remove_consequtive_quotes(data->input);
	tokenizer(&data->token_lst, data->input);
	expand_token_lst(&data->token_lst);
	print_full_token_data(data);
	// if (parser_err == -1) // checks if redirect (and what else?) are OK
	// if (interpreter == -1) // fills smd_struct
	free_token_lst(&data->token_lst);
	return (0);
}
