

#include "../../includes/minishell.h"

int parser(t_data *data)
{
	//expander
	tokenizer(&data->token_lst, data->input);

	t_token *tmp;
	tmp = data->token_lst;
	while (tmp)
		{
			printf("TOKEN: %s TYPE: %d\n", tmp->string, tmp->type);
			tmp = tmp->next;
		}
	// if (tokenizer_err(data->token_lst) == -1)
	// {
	// 	return (-1);
	// }
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