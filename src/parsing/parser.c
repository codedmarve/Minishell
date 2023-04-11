

#include "../../includes/minishell.h"

void	tokenizer(t_token **token_ll, char *exp)
{
	t_token	*token;
	int		i;

	i = 0;
	while (exp[i] != '\0')
	{
		if (exp[i] == '\'' || exp[i] == '"')
			token = init_quotes(&exp[i], &i, exp[i]);
		else if (exp[i] == '|' || exp[i] == ' ')
			token = init_pipe_or_sep(&exp[i], &i, exp[i]);
		else if ((exp[i] == '>' && exp[i + 1] != '>') || \
				(exp[i] == '<' && exp[i + 1] != '<'))
			token = init_single_red(exp, &i, exp[i]);
		else if ((exp[i] == '<' && exp[i + 1] == '<') || \
				(exp[i] == '>' && exp[i + 1] == '>'))
			token = init_double_red(exp, &i, exp[i]);
		else
			token = init_word(exp, &i);
		token_add_back(token_ll, token);
	}
}

int parser(t_data *data)
{
	t_token *token_ll;

	tokenizer(&token_ll, data->input);

	t_token *tmp;
	tmp = token_ll;
	while (tmp)
	{
		printf("string: %s type: %d\n", tmp->string, tmp->type);
		tmp = tmp->next;
	}
	return (0);
}