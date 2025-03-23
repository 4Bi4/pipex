/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labia-fe <labia-fe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:02:46 by labia-fe          #+#    #+#             */
/*   Updated: 2025/03/23 17:18:09 by labia-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//	Function to free a matrix allocated with malloc
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
