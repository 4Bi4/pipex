/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labia-fe <labia-fe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:18:20 by labia-fe          #+#    #+#             */
/*   Updated: 2025/03/18 19:52:42 by labia-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	get_env(t_struct *data, char **envp)
{
	char	*path;
	int 	i;
	data->path = NULL;
	i = 0;
	while (envp[i])
	{
		if ((path = ft_strnstr(envp[i], "PATH=", 6)))
			break ;
		i++;
	}
	while (*path != '/')
		path++;
	data->path = ft_split(path, ':');
	if (!data->path)
		return (1);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	if (ac < 2)
		return(write(2, "sos boludo metéle algo al programa\n", 36), 1);
	else
	{
		(void)av;
		t_struct *data = malloc(sizeof(t_struct));
		get_env(data, envp);
		int test = 4;
		char	*cmdpath;
		for (int i = 0; data->path[i] && test != 0; i++)
		{
			cmdpath = ft_strjoin(data->path[i], "/cat");
			test = access(cmdpath, F_OK);
		}
		char	*args[] = {"cat", "nice.txt", NULL};
		execve(cmdpath, args, envp);
		perror("perrow: (woof woof)");
		// char *nice = (char *)malloc(sizeof(char) * (6000 + 1));
		// int fd = open("nice.txt", O_RDONLY);
		// read(fd, nice, 6000);
		// sleep(2);
		// printf(YELLOW "%s\n" RESET, nice);
		// sleep(1);
		// write(1, "\n                                                               👍\n", 69);
		return (free(data), 0);
	}
}
