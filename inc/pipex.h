/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:22:46 by gasroman          #+#    #+#             */
/*   Updated: 2024/07/02 17:08:27 by gasroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../libft/fd_printf.h"

# define FALSE					0
# define TRUE					1
# define ERROR				   -1
# define IN_FILE				0
# define OUT_FILE				1

# define CHILD					0

# define ERROR_MALLOC			3
# define ERROR_PATH				4
# define ERROR_FD				5
# define ERROR_CHILD			6
# define ERROR_CMMD_NF			7

# define EXIT_CMMD_NOT_FOUND	127

# define NO_FILE 		"No such file or directory\n"
# define NO_PERMITS		"Permission denied\n"
# define NO_COMMAND		"Command not found\n"
# define NO_ARGUMENTS	"Invalid number of arguments\n"
# define NO_MEMORY 		"Error trying to allocate memory\n"
# define NO_PATH		"command not found\n"
# define NO_PIPE 		"Insert ERROR MESSAGE\n"
# define NO_CHILD 		"ABORT:\n"

typedef struct s_token
{
	int					status;
	int					file;
	int					fd_pipes[2];
	int					pid;
	int					tmp_fd;
	char				*path_join;
	char				**command;
	struct s_token		*next;
}	t_token;

//#-----pipex.c----#//
int			print_error(int type, int exit_status, char *str);
int			parsing_open(char *file, int *fd, int flag);

//#-----init.c-----#//
char		*find_path(char **env);
char		*path_join(char *path, char *command);
t_token		*init_tokens(int ac, char **av, char **env);
int			init_child(t_token **token, char **env);
int			exec_child(t_token **token, char **env);

//#-----aux.c------#//
void		ft_add_token_back(t_token **token, t_token *new);
t_token		*ft_tokenlast(t_token *token);
void		free_tokens(t_token **token);
void		free_double(char **ptr);

#endif
