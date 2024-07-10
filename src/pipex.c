/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:09:39 by gasroman          #+#    #+#             */
/*   Updated: 2024/07/10 18:01:38 by gasroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	print_error(int type, int exit_status, char *str)
{
	int	tmp;

	tmp = (type == 1) && fd_printf(2, "Pipex: %s: %s", str, NO_ARGUMENTS);
	tmp = (type == 2) && fd_printf(2, "Pipex: %s: %s", str, NO_COMMAND);
	tmp = (type == 3) && fd_printf(2, "Pipex: %s: %s", str, NO_MEMORY);
	tmp = (type == 4) && fd_printf(2, "Pipex: %s: %s", str, NO_PATH);
	tmp = (type == 5) && fd_printf(2, "Pipex: %s: %s", str, NO_PIPE);
	tmp = (type == 6) && fd_printf(2, "Pipex: %s: %s", str, NO_CHILD);
	tmp = (type == 7) && fd_printf(2, "Pipex: %s: %s", str, NO_PERMITS);
	if (type == -1)
	{
		fd_printf(2, "Pipex: ");
		perror(str);
	}
	(void)tmp;
	return (exit_status);
}

int	parsing_open(char *file, int *fd, int flag)
{
	int	permits;
	int	mode;
	int	rec;

	rec = ((flag == IN_FILE) * access(file, F_OK | R_OK));
	permits = ((flag == IN_FILE) * O_RDONLY) + \
		((flag == OUT_FILE) * (O_WRONLY | O_CREAT | O_TRUNC));
	mode = ((flag == IN_FILE) * O_RDONLY) + ((flag == OUT_FILE) * 0644);
	*fd = open(file, permits, mode);
	if (rec != 0 || *fd == ERROR)
		return (print_error(ERROR, 1, file));
	return (EXIT_SUCCESS);
}

int	exec_child(t_token **token, char **env)
{
	t_token	*iter;
	int		i;
	int		tmp[2];

	i = -1;
	pipe(tmp);
	iter = *token;
	while (++i < 2)
	{
		iter->pid = fork();
		if (iter->pid == ERROR)
			exit(print_error(ERROR_CHILD, EXIT_FAILURE, "init child"));
		if (iter->pid == CHILD)
			init_child(&iter, env, i, tmp);
		iter = iter->next;
		ft_dup2(tmp[1], tmp[0], STDIN_FILENO);
	}
	dup2(tmp[0], STDIN_FILENO);
	close(tmp[0]);
	dup2(tmp[1], STDOUT_FILENO);
	close(tmp[1]);
	iter = *token;
	pid_waiter(&iter);
	return ((*token)->next->status);
}

int	main(int ac, char **av, char **env)
{
	t_token	*token;
	int		status;

	if (ac != 5)
		return (print_error(1, 1, NULL));
	token = init_tokens(ac, av, env);
	status = exec_child(&token, env);
	free_tokens(&token);
	exit(status);
}
