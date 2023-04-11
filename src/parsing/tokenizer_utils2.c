
#include "../../includes/minishell.h"

t_token	*last_token(t_token *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	token_add_back(t_token **list, t_token *new)
{
	t_token	*last;

	if (*list != NULL)
	{
		last = last_token(*list);
		last->next = new;
	}
	else
		*list = new;
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