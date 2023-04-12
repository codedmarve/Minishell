

#include "../../includes/minishell.h"

int parser(t_data *data)
{
	tokenizer(&data->token_lst, data->input);

	t_token *tmp;
	tmp = data->token_lst;
	int i = 0;
	while (tmp)
		{
			printf("TOKEN nr %i: %s TOK_TYPE: %d QUOTATION: %d\n", i, tmp->string, tmp->type, tmp->quote_type);
			i++;
			tmp = tmp->next;
		}
	return (0);
}
