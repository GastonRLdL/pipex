/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:46:21 by gasroman          #+#    #+#             */
/*   Updated: 2024/07/10 17:54:41 by gasroman         ###   ########.fr       */
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
			exit(print_error(ERROR_MALLOC, EXIT_FAILURE, "init at join"));
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
	while (++i < (ac - 2))
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
		token->argv = av;
		ft_add_token_back(&res, token);
	}
	return (res);
}

int	init_child(t_token **token, char **env, int i, int *tmp)
{
	int	pars;

	pars = 0;
	if (i == 0)
	{
		pars = parsing_open((*token)->argv[1], &(*token)->file, IN_FILE);
		dup2((*token)->file, STDIN_FILENO);
		close((*token)->file);
	}
	else if (i == 1)
	{
		pars = parsing_open((*token)->argv[4], &(*token)->file, OUT_FILE);
		dup2((*token)->file, STDOUT_FILENO);
		close((*token)->file);
	}
	if (pars != 0)
		exit(pars);
	ft_dup2(tmp[0], tmp[1], STDOUT_FILENO);
	execve((*token)->path_join, (*token)->command, env);
	if (errno == ENOENT)
		exit(print_error(ERROR_CMD_NF, EXIT_CMD_NOT_FOUND, *(*token)->command));
	exit(print_error(ERROR_NO_PRMT, EXIT_CMD_ERROR, *(*token)->command));
	return (0);
}

void	pid_waiter(t_token **token)
{
	waitpid((*token)->next->pid, &(*token)->next->status, WUNTRACED);
	(*token)->next->status = WEXITSTATUS((*token)->next->status);
}
