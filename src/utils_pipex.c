/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labia-fe <labia-fe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:02:46 by labia-fe          #+#    #+#             */
/*   Updated: 2025/04/07 01:28:50 by labia-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//	Function to free a matrix allocated with malloc
//	RETURN VALUES = void function does not return a value
void	free_matrix(char **mtrx)
{
	int	i;

	i = 0;
	if (mtrx)
	{
		while (mtrx[i])
		{
			free(mtrx[i]);
			i++;
		}
		free(mtrx);
	}
	return ;
}

//	Function to free the whole structure allocated with malloc
//	RETURN VALUES = void function does not return a value
void	free_struct(t_struct *data)
{
	if (data)
	{
		if (data->cmd1)
			free_matrix(data->cmd1);
		data->cmd1 = NULL;
		if (data->cmd2)
			free_matrix(data->cmd2);
		data->cmd2 = NULL;
		if (data->path)
			free_matrix(data->path);
		data->path = NULL;
		data->in_fd = 0;
		data->out_fd = 0;
		free(data);
	}
	return ;
}

//	Function to parse the arguments
//	RETURN VALUES = 0 if OK, -1 if error.
int	check_args(char **args, t_struct *data)
{
	char	*temp;

	data->cmd1 = ft_split(args[1], ' ');
	data->cmd2 = ft_split(args[2], ' ');
	if (!data->cmd1 || !*data->cmd1 || !data->cmd2 || !*data->cmd2)
		return (write(2, "Wrong Commands or Malloc Error\n", 31), -1);
	temp = data->cmd1[0];
	data->cmd1[0] = check_cmd(data, data->cmd1);
	free(temp);
	if (!data->cmd1[0])
		return (-1);
	temp = data->cmd2[0];
	data->cmd2[0] = check_cmd(data, data->cmd2);
	free(temp);
	if (!data->cmd2[0])
   		return (-1);
	return (0);
}

//	Function to check if a command exists and is executable
//	RETURN VALUES = command absolute path if OK, NULL if error.
char	*check_cmd(t_struct *data, char **command)
{
	char	*cmdpath;
	char	*cmd;
	int		ret;
	int		i;

	i = 0;
	ret = -1;
	cmdpath = NULL;
	cmd = ft_strjoin("/", command[0]);
	while (data->path[i] && ret != 0)
	{
		if (cmdpath)
			free(cmdpath);
		cmdpath = ft_strjoin(data->path[i], cmd);
		ret = access(cmdpath, F_OK);
		i++;
	}
	free(cmd);
	if (ret != 0)
		return (perror("command not found"), free(cmdpath), NULL);
	if (access(cmdpath, X_OK) != 0)
		return (perror("can't execute file"), free(cmdpath), NULL);
	return (cmdpath);
}
