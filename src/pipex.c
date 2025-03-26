/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labia-fe <labia-fe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:13:07 by labia-fe          #+#    #+#             */
/*   Updated: 2025/03/27 00:04:56 by labia-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//	if(!data->cmd2[0])
//		vacia el outfile si existe y o crea uno vacio si no existe
//	if(!data->cmd1[0])
//		ejecuta el 2do comando sin input
//	else
//		haz todo

void	master_mind(t_struct *data)
{
	int	pipx[2];
	
	if (!data->cmd2[0])
		return ;
	if (!data->cmd1[0])
			//	funcion de 2nd command sin input
		return ;
	if (pipe(pipx) < 0)
	{
		perror("pipe error");
		return ;
	}
		//	funcion de 1st command
		//	funcion de 2nd command
}

//	Function to extract the "PATH" from all the enviroment data
//	RETURN VALUES = 0 if ok, 1 if error.
int	get_env(t_struct *data, char **envp)
{
	char	*path;
	int		i;

	data->path = NULL;
	i = 0;
	while (envp[i])
	{
		path = ft_strnstr(envp[i], "PATH=", 6);
		if (path)
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
			return (write(2, "¡[ERROR]! Malloc error\n", 24), 1);
		get_env(data, envp);
		if (check_args(&argv[1], data) != 0)
			return (free_struct(data), 1);
		data->in_fd = open(argv[1], O_RDONLY);
		if (data->in_fd < 0)
			perror(argv[1]);
		data->out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->out_fd < 0)
			perror(argv[4]);
		master_mind(data);
		return (free_struct(data), 0);
	}
}
