/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labia-fe <labia-fe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:17:09 by labia-fe          #+#    #+#             */
/*   Updated: 2025/03/23 18:33:17 by labia-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//	Function to parse the arguments
int	check_args(char **args, t_struct *data)
{
	if (access(args[0], F_OK) != 0 || access(args[0], R_OK) != 0)
	{
		write(2, "¡[ERROR]! Input File not found or bad permissions\n", 51);
		return (1);
	}
	data->cmd1 = ft_split(args[1], ' ');
	data->cmd2 = ft_split(args[2], ' ');
	if (check_cmd(data, data->cmd1) != 0 || check_cmd(data, data->cmd2) != 0)
		return (1);
	return (0);
}

//	Function to check if a command exists and is executable
int	check_cmd(t_struct *data, char **command)
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
		return (perror("command not found"), free(cmdpath), 1);
	if ((access(cmdpath, X_OK)) != 0)
		return (perror("can't execute file (permissions?)"), free(cmdpath), 1);
	return (free(cmdpath), 0);
}

// int	execute_cmd(t_struct *data, char **envp)
// {
	
// }
