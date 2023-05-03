
#include "../../includes/minishell.h"

int	parser(t_data *data)
{
	remove_consequtive_quotes(data->input);
	tokenizer(&data->token_lst, data->input);
	expand_token_lst(&data->token_lst);
	return (0);
}
