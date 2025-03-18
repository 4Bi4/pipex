/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labia-fe <labia-fe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:18:16 by labia-fe          #+#    #+#             */
/*   Updated: 2025/03/18 19:42:14 by labia-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include "../src/libft/libft.h"

# define YELLOW  "\x1b[93m"
# define RESET   "\x1b[0m"

typedef	struct s_struct
{
	char	*cmd1;
	char	*cmd2;

	int		ifd;
	int		ofd;

	char	**path;

}	t_struct;

#endif