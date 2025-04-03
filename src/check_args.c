/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labia-fe <labia-fe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:17:09 by labia-fe          #+#    #+#             */
/*   Updated: 2025/04/02 20:19:29 by labia-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//	Function to parse the arguments
//	RETURN VALUES = 0 if OK, 1 if error.
int	check_args(char **args, t_struct *data)
{
	char	*temp;
	
	data->cmd1 = ft_split(args[1], ' ');
	data->cmd2 = ft_split(args[2], ' ');
	temp = data->cmd1[0];
	data->cmd1[0] = check_cmd(data, data->cmd1);
	free(temp);
	temp = data->cmd2[0];
	data->cmd2[0] = check_cmd(data, data->cmd2);
	free(temp);
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
		return (perror("can't execute file (permissions?)"), free(cmdpath), NULL);
	return (cmdpath);
}
