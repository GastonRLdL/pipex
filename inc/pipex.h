/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:22:46 by gasroman          #+#    #+#             */
/*   Updated: 2024/07/10 14:55:22 by gasroman         ###   ########.fr       */
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

# define ERROR_CMD_NF			2
# define ERROR_MALLOC			3
# define ERROR_PATH				4
# define ERROR_FD				5
# define ERROR_CHILD			6
# define ERROR_NO_PRMT			7

# define EXIT_CMD_NOT_FOUND	  127
# define EXIT_CMD_ERROR		  126

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
	int					pid;
	int					tmp_fd;
	char				*path_join;
	char				**command;
	char				**argv;
	struct s_token		*next;
}	t_token;

//#-----pipex.c----#//
int			print_error(int type, int exit_status, char *str);
int			parsing_open(char *file, int *fd, int flag);
int			init_child(t_token **token, char **env, int i, int *tmp);

//#-----init.c-----#//
char		*find_path(char **env);
char		*path_join(char *path, char *command);
t_token		*init_tokens(int ac, char **av, char **env);
int			exec_child(t_token **token, char **env);
void		pid_waiter(t_token **token);

//#-----aux.c------#//
void		ft_add_token_back(t_token **token, t_token *new);
t_token		*ft_tokenlast(t_token *token);
void		free_tokens(t_token **token);
void		free_double(char **ptr);
int			ft_dup2(int prev, int curr, int std);

void		print_token(t_token *token);
#endif
