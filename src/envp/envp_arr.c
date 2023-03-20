


#include "../../includes/minishell.h"

/* 
envp_var_counter:
counts how many original environment variables there are.
*/

int	envp_variable_counter(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

/*
nitializes a data variable with the contents of the environment
variables received from the original shell
*/
int	init_envp_arr(t_data *data, char **envp)
{
	int		i;

	data->envp_arr = ft_calloc(envp_variable_counter(envp) + 1, sizeof(char *)); //sizeof * data->envp_arr);
	if (!data->envp_arr)
		return (0);
	i = 0;
	while (envp[i])
	{
		data->envp_arr[i] = ft_strdup(envp[i]);
		if (!data->envp_arr[i])
			return (0);
		i++;
	}
	return (1);
}
