

#include "../../includes/minishell.h"

char	*ft_strdup2(const char *str, int len)
{
	char	*dup;
	int		i;

	i = 0;
	dup = ft_calloc(len + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
