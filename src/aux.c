/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:02:00 by gasroman          #+#    #+#             */
/*   Updated: 2024/07/02 17:11:10 by gasroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_add_token_back(t_token **token, t_token *new)
{
	t_token	*temp;

	if (token)
	{
		if (!*token)
			*token = new;
		else
		{
			temp = ft_tokenlast(*(token));
			temp->next = new;
		}
	}
}

t_token	*ft_tokenlast(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

void	free_tokens(t_token **token)
{
	t_token	*temp;
	t_token	*aux;

	temp = *token;
	while (temp)
	{
		close(temp->file);
		close(temp->fd_pipes[0]);
		close(temp->fd_pipes[1]);
		free_double(temp->command);
		free(temp->path_join);
		aux = temp->next;
		free(temp);
		temp = aux;
	}
	*token = NULL;
}

void	free_double(char **ptr)
{
	int	i;

	i = -1;
	if (ptr)
	{
		while (ptr[++i])
			free(ptr[i]);
		free(ptr);
	}
}
