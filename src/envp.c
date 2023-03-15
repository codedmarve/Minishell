

#include "../includes/minishell.h"

int	envp_size(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i + 1);
}

/*
saves envp
*/

char	**envp_copy(t_data *data, char **envp)
{
	int	i;
	char **envp_copy;
	
	envp_copy = ft_calloc(envp_size(envp));
	if (!envp_copy)
	{
		printf("Error: ft_calloc (copy_env)\n");
		exit(1);
	}
	i = 0;
	while (envp[i])
	{
		envp_copy[i] = ft_strdup(envp[i]);
		i++;
	}
}