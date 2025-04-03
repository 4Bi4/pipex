/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labia-fe <labia-fe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:13:07 by labia-fe          #+#    #+#             */
/*   Updated: 2025/04/02 20:21:25 by labia-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//	Function that handles the 1st fork and the execution of the 1st cmd
//	RETURN VALUES = 0 if OK, -1 if error (the child process doesnt return)
int	first_exec(t_struct *data, int *pipx, char *cmdpath)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (write(2, "Internal error, pls try again1\n", 31), -1);
	if (pid == 0)
	{
		if (dup2(data->in_fd, STDIN_FILENO) == -1)
			return (perror("dup2 error"), exit(1), -1);
		close(data->in_fd);
		if (dup2(pipx[1], STDOUT_FILENO) == -1)
			return (perror("dup2 error"), exit(1), -1);
		close(pipx[0]);
		if (execve(cmdpath, data->cmd1, data->path) == -1)
		{
			perror("Internal error");
			exit(EXIT_FAILURE);
		}
	}
	else
		return (0);
}

//	Function that handles the 2nd fork and the execution of the 2nd cmd
//	RETURN VALUES = 0 if OK, -1 if error (the child process doesnt return)
int	second_exec(t_struct *data, int *pipx, char *cmdpath)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (write(2, "Internal error, pls try again01\n", 32), -1);
	if (pid == 0)
	{
		if (dup2(pipx[0], STDIN_FILENO) == -1)
			return (perror("dup2 error"), exit(1), -1);
		close(pipx[1]);
		if (dup2(data->out_fd, STDOUT_FILENO) == -1)
			return (perror("dup2 error"), exit(1), -1);
		close(data->out_fd);
		if (!execve(cmdpath, data->cmd2, data->path))
		{
			perror("Internal error 2");
			exit(EXIT_FAILURE);
		}
	}
	else
		return (0);
}


//	Function in charge of executing the steps in order and optimizing resources
//	RETURN VALUES = void function does not return a value
void	master_mind(t_struct *data)
{
	char	*path1;
	char	*path2;
	int		pipx[2];

	path1 = check_cmd(data, data->cmd1);
	path2 = check_cmd(data, data->cmd2);
	printf("%s\n%s\n", path1, path2);
	if (!data->cmd2[0])
		return ;
	if (!data->cmd1[0])
		second_exec(data, pipx, path2);
	if (pipe(pipx) < 0)
	{
		perror("pipe error");
		return ;
	}
	else
	{
		first_exec(data, pipx, path1);
		second_exec(data, pipx, path2);
	}
	return ;
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
