
#include "../../includes/minishell.h"

void	token_add_back(t_token **list, t_token *new)
{
	if (!list || !new)
		return ;
	if (!*list)
		*list = new;
	else
		token_last(*list)->next = new;
}

t_token	*token_last(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if (!list)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	remove_quotes(char *s)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] == '\'')
		{
			len -= 2;
			remove_quotes_helper(s, s[i], &i, &j);
		}
		else if (s[i] == '"')
		{
			len -= 2;
			remove_quotes_helper(s, s[i], &i, &j);
		}
		s[j] = s[i];
		j++;
		i++;
	}
	s[j] = '\0';
}

void	remove_quotes_helper(char *s, char q, int *i, int *j)
{
	*i = *i + 1;
	while (s[*i] != q)
	{
		s[*j] = s[*i];
		*i = *i + 1;
		*j = *j + 1;
	}
	*i = *i + 2;
	*j = *j + 1;
}