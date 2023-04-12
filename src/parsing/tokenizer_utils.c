
#include "../../includes/minishell.h"

void	token_add_back(t_token **lst, t_token *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		token_last(*lst)->next = new;
}

t_token	*token_last(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	remove_quotes(char *s)
{
	int	len;

	len = ft_strlen(s);
	if ((len >= 2 && s[0] == '"' && s[len - 1] == '"')
		|| (len >= 2 && s[0] == '\'' && s[len - 1] == '\''))
	{
		ft_memmove(s, s + 1, len - 2);
		s[len - 2] = '\0';
	}
}

// void	remove_quotes(char *str)
// {
// 	int	i;
// 	int	j;
// 	int	len;

// 	i = 0;
// 	j = 0;
// 	len = ft_strlen(str);
// 	while (i < len)
// 	{
// 		if (str[i] == '\'')
// 		{
// 			len -= 2;
// 			remove_quotes_helper(str, str[i], &i, &j);
// 		}
// 		else if (str[i] == '"')
// 		{
// 			len -= 2;
// 			remove_quotes_helper(str, str[i], &i, &j);
// 		}
// 		str[j] = str[i];
// 		j++;
// 		i++;
// 	}
// 	str[j] = '\0';
// }

// void	remove_quotes_helper(char *str, char quote, int *i, int *j)
// {
// 	*i = *i + 1;
// 	while (str[*i] != quote)
// 	{
// 		str[*j] = str[*i];
// 		*i = *i + 1;
// 		*j = *j + 1;
// 	}
// 	*i = *i + 2;
// 	*j = *j + 1;
// }

// void	token_add_back(t_token **lst, t_token *new)
// {
// 	t_token	*last;

// 	if (*lst != NULL)
// 	{
// 		last = token_last(*lst);
// 		last->next = new;
// 	}
// 	else
// 		*lst = new;
// }

// t_token	*token_last(t_token *lst)
// {
// 	if (lst == NULL)
// 		return (NULL);
// 	while (lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
// }
