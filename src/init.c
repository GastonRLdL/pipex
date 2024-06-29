/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:46:21 by gasroman          #+#    #+#             */
/*   Updated: 2024/06/26 16:19:17 by gasroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*find_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			return (env[i] + 5);
	}
	exit(print_error(ERROR_PATH, EXIT_FAILURE, "ENVIRONMENT PATH not found"));
}

char	*path_join(char *path, char *command)
{
	char	**split_path;
	char	*join;
	char	*at_slash;
	int		i;

	split_path = ft_split(path, ':');
	if (!split_path)
		exit(print_error(ERROR_MALLOC, EXIT_FAILURE, "init split path"));
	i = -1;
	while (split_path[++i])
	{
		at_slash = ft_strjoin(split_path[i], "/");
		if (!at_slash)
			exit(print_error(ERROR_MALLOC, EXIT_FAILURE, "init at slash"));
		join = ft_strjoin(at_slash, command);
		if (!join)
			exit(print_error(ERROR_MALLOC, EXIT_FAILURE, "init join"));
		if (!access (join, F_OK))
			return (free(at_slash), clear_split(split_path), join);
		double_free(&at_slash, &join);
	}
	return (clear_split(split_path), ft_strdup(command));
}

t_token	*init_tokens(int ac, char **av, char **env)
{
	t_token	*token;
	t_token	*res;
	int		num_cmmd;
	int		i;

	num_cmmd = 1;
	i = -1;
	res = NULL;
	while (++i < (ac - 3))
	{
		token = ft_calloc(1, sizeof(t_token));
		if (!token)
			exit(print_error(ERROR_MALLOC, EXIT_FAILURE, "init token"));
		token->command = ft_split(av[++num_cmmd], ' ');
		if (!token->command)
			exit(print_error(ERROR_MALLOC, EXIT_FAILURE, "init command"));
		token->path_join = path_join(find_path(env), token->command[0]);
		if (!token->path_join)
			exit(print_error(ERROR_MALLOC, EXIT_FAILURE, "init path join"));
		token->status = 0;
		ft_add_token_back(&res, token);
		// if (i == 0)
		// 	res = token;
		// //token->next = res;
		// token = token->next;
	}
	return (res);
}

int	init_child(t_token **token, char **env)
{
	if (pipe((*token)->fd_pipes) == ERROR)
		exit(print_error(ERROR_FD, EXIT_FAILURE, "init pipe"));
	(*token)->pid = fork();
	if ((*token)->pid == ERROR)
		exit(print_error(ERROR_CHILD, EXIT_FAILURE, "init child"));
	if ((*token)->pid == CHILD)
	{
		close((*token)->fd_pipes[0]);
		dup2((*token)->fd_pipes[1], STDOUT_FILENO);
		close((*token)->fd_pipes[1]);
		dup2((*token)->tmp_fd, STDIN_FILENO);
		close((*token)->tmp_fd);
		execve((*token)->path_join, (*token)->command, env);
		exit(127); //Testear posibles casos, ty caro <3
	}
	close((*token)->fd_pipes[1]);
	close((*token)->tmp_fd);
	(*token)->tmp_fd = (*token)->fd_pipes[0];
	return (0);
}

int	exec_child(t_token **token, char **env)
{
	t_token	*iter;
	int		i;

	iter = *token;
	while (iter != NULL)
	{
		init_child(&iter, env);
		iter = iter->next;
	}
	i = -1;
	while (++i < 2)
		waitpid(-1, NULL, WUNTRACED);
	return (0);
}
