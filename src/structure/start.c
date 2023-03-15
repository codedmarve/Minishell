/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:10:25 by moduwole          #+#    #+#             */
/*   Updated: 2023/03/13 18:10:25 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	welcome(int argc, char **argv)
{
	if (argc > 1 || argv[1])
		exit(printf("Error: programme can't take argument(s)\n") - 39);


	printf("%s   ****************************************\n",
		"\033[0;32m");
	printf("   *   Welcome to Minishell               *\n");
	printf("   *                                      *\n");
	printf("   *%s   Created by Marvellous and Daria    %s*\n",
		"\033[0;33m", "\033[0;32m");
	printf("   ****************************************\n%s",
		"\033[0m");
}

int	ft_readline(t_data *data)
{

	printf("%s", "\e[0;38;5;28m");
	data->line = readline(data->prompt);
	printf("%s", data->line);
	free(data->line);

	return (1);
}

int	get_prompt2(char **env, t_data *data, char *pwd, int *fd)
{
	int		i;
	char	*tmp;
	char 	*tmp2;

	i = 0;
	read(fd[0], pwd, 1000);
	pwd[ft_strlen(pwd) - 1] = '\0';
	while(env[i])
	{
		if (strncmp(env[i], "USER=", 5) == 0)
		{
			tmp = ft_strjoin(&env[i][5], "@minishell:\e[1;34m");
			break ;
		}
		i++;
	}
	if (!tmp)
		tmp = ft_strdup("user@minishell:\e[1;34m");
	tmp2 = ft_strjoin(pwd, "\033[0m$ ");
	data->prompt = ft_strjoin(tmp, tmp2);
	return (free(tmp), free(tmp2), 1);
}


int	get_prompt(char **env, t_data *data)
{
	int		fd[2];
	char	pwd[1000];
	char	**cmd_mac;
	char	**cmd_linux;

    pipe(fd);
	ft_bzero(pwd, 1000);
	cmd_mac = ft_split("/bin/pwd", ' ');
	cmd_linux = ft_split("/usr/bin/pwd", ' ');
	if (fork() == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		if (access("/usr/bin/pwd", X_OK) == 0)
			execve("/usr/bin/pwd", cmd_linux, NULL);
		else if (access("/bin/pwd", X_OK) == 0)
			execve("/bin/pwd", cmd_mac, NULL);
		else
			return (ft_printf("-"), 0);
	}
	get_prompt2(env, data, pwd, fd);
	free(cmd_linux[0]);
	free(cmd_mac[0]);
	free(cmd_linux);
	free(cmd_mac);
}
