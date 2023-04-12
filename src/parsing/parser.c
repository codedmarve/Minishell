

#include "../../includes/minishell.h"

int parser(t_data *data)
{
	tokenizer(&data->token_ll, data->input);

	t_token *tmp;
	tmp = data->token_ll;
	while (tmp)
		{
			printf("TOKEN: %s TYPE: %d\n", tmp->string, tmp->type);
			tmp = tmp->next;
		}
	return (0);
}

// int parser(t_data *data)
// {
// 	t_token *token_ll;

// 	tokenizer(&token_ll, data->input);

// 	t_token *tmp;
// 	tmp = token_ll;
// 	if (tmp)
// 	{
// 		printf("ENTIRE STRING: %s\n", tmp->string);
// 		tmp = tmp->next;
// 		while (tmp)
// 		{
// 			printf("TOKEN: %s TYPE: %d\n", tmp->string, tmp->type);
// 			tmp = tmp->next;
// 		}
// 	}
// 	return (0);
// }