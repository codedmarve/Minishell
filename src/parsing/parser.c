

#include "../../includes/minishell.h"

void dollar_check(char *s)
{
	while (*s)
	{
		if (*s == '$')
		{
			printf("%s\n", s);
			printf("expander needed\n");
			return ;
		}
		s++;
	}
}

void expander(t_token **token_lst)
{
	t_token *tmp;

	tmp = *token_lst;
	while (tmp)
	{
		if (tmp->quote_type == S_Q)
		{
			tmp = tmp->next;
			continue ;
		}
		dollar_check(tmp->string);
		tmp = tmp->next;
	}
}

void	print_after_tokenizer(t_data *data)
{
	t_token	*tmp;
	int		 i;

	tmp = data->token_lst;
	i = 0;
	while (tmp)
		{
			printf("TOKEN nr %i: %s TOK_TYPE: %d QUOTATION: %d\n",
				i, tmp->string, tmp->type, tmp->quote_type);
			i++;
			tmp = tmp->next;
		}
}

int parser(t_data *data)
{
	tokenizer(&data->token_lst, data->input);
	print_after_tokenizer(data);
	expander(&data->token_lst);
	return (0);
}

