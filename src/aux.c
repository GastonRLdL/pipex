/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:02:00 by gasroman          #+#    #+#             */
/*   Updated: 2024/06/26 13:48:10 by gasroman         ###   ########.fr       */
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
