

#include "../../includes/minishell.h"

int parser(t_data *data)
{
	tokenizer(&data->token_lst, data->input);

	t_token *tmp;
	tmp = data->token_lst;
	while (tmp)
		{
			printf("TOKEN: %s TYPE: %d Q: %d\n", tmp->string, tmp->type, tmp->quote_type);
			tmp = tmp->next;
		}
	return (0);
}
