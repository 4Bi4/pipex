/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labia-fe <labia-fe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:13:07 by labia-fe          #+#    #+#             */
/*   Updated: 2025/04/07 00:29:10 by labia-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//	Function that handles the 1st fork and the execution of the 1st cmd
//	RETURN VALUES = 0 if OK, -1 if error (the child process doesnt return)
int	first_exec(t_struct *data, int *pipx, char *cmdpath, pid_t pid)
{
	if (pid < 0)
		return (perror("fork error"), exit(1), -1);
	if (pid == 0)
	{
		if (dup2(data->in_fd, STDIN_FILENO) == -1)
			return (perror("dup2 error"), exit(1), -1);
		close(data->in_fd);
		if (dup2(pipx[1], STDOUT_FILENO) == -1)
			return (perror("dup2 error"), exit(1), -1);
		close(pipx[0]);
		if (execve(cmdpath, data->cmd1, data->path) == -1)
			return (perror("Internal error"), exit(1), 1);
	}
	waitpid(pid, 0, 0);
	return (0);
}

//	Function that handles the 2nd fork and the execution of the 2nd cmd
//	RETURN VALUES = 0 if OK, -1 if error (the child process doesnt return)
int	second_exec(t_struct *data, int *pipx, char *cmdpath, pid_t pid)
{
	if (pid < 0)
		return (perror("fork error"), exit(1), -1);
	if (pid == 0)
	{
		if (dup2(pipx[0], STDIN_FILENO) == -1)
			return (perror("dup2 error"), exit(1), -1);
		close(pipx[1]);
		if (dup2(data->out_fd, STDOUT_FILENO) == -1)
			return (perror("dup2 error"), exit(1), -1);
		close(data->out_fd);
		if (!execve(cmdpath, data->cmd2, data->path))
			return (perror("Internal error"), exit(1), 1);
	}
	return (0);
}

//	Function in charge of executing the steps in order and optimizing resources
//	RETURN VALUES = 0 if OK, -1 if error
int	master_mind(t_struct *data)
{
	pid_t	pid;
	pid_t	pid2;
	int		pipx[2];

	if (!data->cmd2[0])
		return (1);
	if (!data->cmd1[0])
	{
		pid = fork();
		if (pid == 0)
			second_exec(data, pipx, data->cmd2[0], pid);
	}
	if (pipe(pipx) < 0)
		return (perror("pipe error"), exit(1), 1);
	else
	{
		pid = fork();
		if (pid == 0)
			first_exec(data, pipx, data->cmd1[0], pid);
		pid2 = fork();
		if (pid2 == 0)
			second_exec(data, pipx, data->cmd2[0], pid2);
	}
	waitpid(pid, 0, 0);
	return (0);
}

//	Function to extract the "PATH" from all the enviroment data
//	RETURN VALUES = 0 if ok, -1 if error
int	get_env(t_struct *data, char **envp)
{
	char	*path;
	int		i;

	data->path = NULL;
	i = 0;
	while (envp[i])
	{
		path = ft_strnstr(envp[i], "PATH=", 5);
		if (path)
			break ;
		i++;
	}
	if (!path)
		return (-1);
	while (*path != '/')
		path++;
	data->path = ft_split(path, ':');
	if (!data->path)
		return (-1);
	return (0);
}

//	Main Function (program starts here)
//	RETURN VALUES = 0 if ok, 1 if error
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
		if (get_env(data, envp) != 0)
			return (free_struct(data), 1);
		if (check_args(&argv[1], data) != 0)
			return (free_struct(data), 1);
		data->in_fd = open(argv[1], O_RDONLY);
		if (data->in_fd < 0)
			return (perror(argv[1]), free_struct(data), 1);
		data->out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->out_fd < 0)
			return (perror(argv[4]), free_struct(data), 1);
		master_mind(data);
		return (free_struct(data), 0);
	}
}
