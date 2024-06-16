/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:09:39 by gasroman          #+#    #+#             */
/*   Updated: 2024/06/16 06:19:03 by gasroman         ###   ########.fr       */
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


int	print_error(int type, int exit_status, char *str)
{
	int	tmp;

	tmp = (type == 1) && fd_printf(2, "Pipex: %s: %s", str, NO_ARGUMENTS);
	tmp = (type == 2) && fd_printf(2, "Pipex: %s: %s", str, NO_COMMAND);
	tmp = (type == 3) && fd_printf(2, "Pipex: %s: %s", str, NO_MEMORY);
	if (type == -1)
		perror("Pipex");
	(void)tmp;
	return (exit_status);
}

int	parsing_open(char *file, int *fd, int flag)
{
	int	permits;
	int	mode;
	int	rec;

	rec = ((flag == IN_FILE) * access(file, F_OK | R_OK));
	permits = ((flag == IN_FILE) * O_RDONLY | O_WRONLY) + ((flag == OUT_FILE)
			* (O_WRONLY | O_CREAT | O_TRUNC));
	mode = ((flag == IN_FILE) * O_RDONLY) + ((flag == OUT_FILE)
			* 0644);
	*fd = open(file, permits, mode);
	if (rec != 0 || *fd == ERROR)
		return (print_error(ERROR, 1, file));
	return (EXIT_SUCCESS);
}



int	main(int ac, char **av, char **env)
{
	t_pipex	pipx;
	t_token	f_cmmd;
	t_token	s_cmmd;
	int		fd_src;
	int		fd_out;

	(void)env;
	(void)av;
	(void)ac;
	if (ac != 5)
		return (print_error(1, 1, NULL));
	
	init_pipx(pipx, ac, av);
	//pipx.path = get_path(env);
	//printf("The path to this enviroment is: %s\n", pipx.path);
	parsing_open(av[1], &fd_src, IN_FILE);
	parsing_open(av[4], &fd_out, OUT_FILE);
	return (0);
}
