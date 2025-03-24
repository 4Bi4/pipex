
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labia-fe <labia-fe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:13:07 by labia-fe          #+#    #+#             */
/*   Updated: 2025/03/19 18:05:45 by labia-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


//	Function to get the "PATH" out of all the enviroment
//	RETURN VALUES = 0 if ok, 1 if error.
int	get_env(t_struct *data, char **envp)
{
	char	*path;
	int		i;

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


//	Main Function (program starts here)
//	RETURN VALUES = 0 if ok, 1 if error.
int	main(int argc, char **argv, char **envp)
{
	t_struct	*data;

	if (argc != 5)
		return (write(2, "usage: infile \"cmd 1\" \"cmd 2\" outfile\n", 38), 1);
	else
	{
		data = ft_calloc(1, sizeof(t_struct));
		if (!data)
			return(write(2, "¡[ERROR]! Malloc error\n", 24), 1);
		get_env(data, envp);
		if (check_args(&argv[1], data) != 0)
			return (free_struct(data), 1);
		return (free_struct(data), 0);
	}
}
