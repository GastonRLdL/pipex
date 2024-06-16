/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:22:46 by gasroman          #+#    #+#             */
/*   Updated: 2024/06/16 06:35:41 by gasroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../libft/fd_printf.h"

# define FALSE			0
# define TRUE			1
# define ERROR		   -1
# define IN_FILE		0
# define OUT_FILE		1
# define ERROR_MALLOC	3
# define ERROR_PATH		4

# define NO_FILE 		"No such file or directory\n"
# define NO_PERMITS		"Permission denied\n"
# define NO_COMMAND		"Command not found\n"
# define NO_ARGUMENTS	"Invalid number of arguments\n"
# define NO_MEMORY 		"Error trying to allocate memory\n"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	char	*path;
	char	*in_file;
	char	*out_file;
	char	*cmmd1;
	char	*cmmd2;

}	t_pipex;

typedef struct s_token
{
	int				status;
	char			*path_join;
	char			**command;
	struct s_token	*next;
}	t_token;

#endif