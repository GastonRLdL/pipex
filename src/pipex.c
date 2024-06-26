/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:09:39 by gasroman          #+#    #+#             */
/*   Updated: 2024/06/29 12:21:22 by gasroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int print_error(int type, int exit_status, char *str)
{
	int tmp;

	tmp = (type == 1) && fd_printf(2, "Pipex: %s: %s", str, NO_ARGUMENTS);
	tmp = (type == 2) && fd_printf(2, "Pipex: %s: %s", str, NO_COMMAND);
	tmp = (type == 3) && fd_printf(2, "Pipex: %s: %s", str, NO_MEMORY);
	tmp = (type == 4) && fd_printf(2, "Pipex: %s: %s", str, NO_PATH);
	tmp = (type == 5) && fd_printf(2, "Pipex: %s: %s", str, NO_PIPE);
	tmp = (type == 6) && fd_printf(2, "Pipex: %s: %s", str, NO_CHILD);
	if (type == -1)
		perror("Pipex");
	(void)tmp;
	return (exit_status);
}

int parsing_open(char *file, int *fd, int flag)
{
	int permits;
	int mode;
	int rec;

	rec = ((flag == IN_FILE) * access(file, F_OK | R_OK));
	permits = ((flag == IN_FILE) * O_RDONLY | O_WRONLY) + ((flag == OUT_FILE) * (O_WRONLY | O_CREAT | O_TRUNC));
	mode = ((flag == IN_FILE) * O_RDONLY) + ((flag == OUT_FILE) * 0644);
	*fd = open(file, permits, mode);
	if (rec != 0 || *fd == ERROR)
		return (print_error(ERROR, 1, file));
	return (EXIT_SUCCESS);
}

void	print_double(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		ft_printf("\t%s\n", array[i]);
}

static void	print_token(t_token *token)
{
	while(token)
	{
		printf("Status: %d\n", token->status);
		printf("Fd_pipes[0]: %d\n", token->fd_pipes[0]);
		printf("Fd_pipes[1]: %d\n", token->fd_pipes[1]);
		printf("Pid: %d\n", token->pid);
		printf("Tmp_fd: %d\n", token->tmp_fd);
		printf("Path_join: %s\n", token->path_join);
		printf("Command: \n");
		print_double(token->command);
		token = token->next;
	}
}

int main(int ac, char **av, char **env)
{
	t_token *token;
	int fd_in;
	int fd_out;

	(void)ac;
	(void)av;
	(void)env;
	if (ac != 5)
		return (print_error(1, 1, NULL));
	parsing_open(av[1], &fd_in, IN_FILE);
	parsing_open(av[4], &fd_out, OUT_FILE);
	token = init_tokens(ac, av, env);
	if (!token)
		ft_printf("soy NULL:\n");
	init_child(&token, env);
	exec_child(&token, env);
	print_token(token);
	//print_token(token->next);
	// exec_child(&token, env);
	return (0);
}
