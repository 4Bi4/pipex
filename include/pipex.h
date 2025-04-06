/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labia-fe <labia-fe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:18:16 by labia-fe          #+#    #+#             */
/*   Updated: 2025/04/06 20:31:52 by labia-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../src/libft/libft.h"

# define YELLOW  "\x1b[93m"
# define RESET   "\x1b[0m"

//	Auxiliary data struct
typedef struct s_struct
{
	char	**cmd1;
	char	**cmd2;

	int		in_fd;
	int		out_fd;

	char	**path;

}	t_struct;

int		check_args(char **args, t_struct *data);
char	*check_cmd(t_struct *data, char	**command);

void	free_matrix(char **mtrx);
void	free_struct(t_struct *data);

#endif