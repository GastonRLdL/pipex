/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:46:21 by gasroman          #+#    #+#             */
/*   Updated: 2024/06/16 06:33:36 by gasroman         ###   ########.fr       */
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

char	*is_access(char *comand, char *tmp_path)
{

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
		if (!acces (join, F_OK))
			return (free(at_slash), clear_split(split_path), join);
		double_free(&at_slash, &join);
	}
	return (clear_split(split_path), ft_strdup(command));
}

t_token	*init_tokens(int ac, char **av, char **env)
{
	t_token	*token;
	int		num_cmmd;
	int		i;

	num_cmmd = 1;
	i = -1;
	while (++i < (ac - 2))
	{
		token = malloc(token);
		if (!token)
			exit(print_error(ERROR_MALLOC, EXIT_FAILURE, "init token"));
		token->command = ft_split(av[i], ' ');
		if (!token->command)
			exit(print_error(ERROR_MALLOC, EXIT_FAILURE, "init command"));
		token->path_join = path_join(find_path(env), token->command[0]);
		if (!token->path_join)
			exit(print_error(ERROR_MALLOC, EXIT_FAILURE, "init path join"));//test memory leaks
		token->status = 0;
		token = token->next;
	}
	token = NULL;
	return (token);
}
