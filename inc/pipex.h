/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:22:46 by gasroman          #+#    #+#             */
/*   Updated: 2024/05/21 12:10:44 by gasroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"

# define FALSE		0
# define TRUE		1
# define ERROR	   -1
# define IN_FILE	0
# define OUT_FILE	1

typedef struct s_token
{
	int				status;
	char			*path_join;
	char			**cmd;
	struct s_token	*next;
}	t_token;

#endif