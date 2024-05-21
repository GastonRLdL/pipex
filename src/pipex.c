/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:09:39 by gasroman          #+#    #+#             */
/*   Updated: 2024/05/21 12:10:39 by gasroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/pipex.h"

/*	1 - En el parceo debemos ver que el cada argumento sea del tipo requerido 
			(ac[1] y ac[4] files y ac[2] y ac[3] comandos)
		En ac[1] debemos comprobar la existenia del archivo a diferecia de ac[4]
			que si no existe debemos comprobar que puede ser creado. De no ser asi
			devolveremos ERROR!.
		En ac[2]y ac[3] implementamos split para corroborar las posibles flags y su validez
		
*/

void	parsing_open(char *file, int *fd, int flag)
{
	int	permits;
	int	mode;

	permits = ((flag == IN_FILE) * O_RDONLY) + ((flag == OUT_FILE)
			* (O_WRONLY | O_CREAT | O_TRUNC));
	mode = ((flag == IN_FILE) * O_RDONLY) + ((flag == OUT_FILE)
			* 0644);
	*fd = open(file, permits, mode);
	if (*fd == ERROR)
		return (printf("Source file does not exist\n"));
}



int	main(int ac, char **av, char **env)
{
	int	fd_src;
	int	fd_out;

	(void)env;
	(void)av;
	(void)ac;
	// if (ac != 5)
	// 	return (0);
	
	// fd_out = open(av[ac - 1], O_RDONLY);
	// if (fd_out == -1)
		// fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// if (fd_out == -1)
	// 	exit (printf("Failed to create fd_out\n"));
	// printf("fd_src = %d\n", fd_src);
	// printf("fd_out = %d\n", fd_out);
	// close(fd_src);
	// close(fd_out);

	// int  i;

	// i = 0;
	// while (++i < ac)
	// {
	// 	ft_printf("The argument %i is: %s\n", i, av[i]);
	// 	if (i == IN_FILE)
	// 		parsing_open(av[i], &fd_src, IN_FILE);

	// }
	// printf("%d, %d", O_RDONLY, (O_WRONLY | O_CREAT | O_TRUNC));
	parsing_open(av[1], &fd_src, IN_FILE);
	parsing_open(av[4], &fd_out, OUT_FILE);
	return (0);
}
