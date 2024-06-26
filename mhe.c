#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
/* ************************************************************************** */
/*  Struct                                                                    */
/* ************************************************************************** */
#define E_EXIT  1
#define ERROR   -1
typedef struct s_micro
{
  int i;
  int n_p;
  int pid;
  int fd[2];
  int tmp_fd;
} t_micro;
/* ************************************************************************** */
/*  Funtions                                                                  */
/* ************************************************************************** */
int fd_putstr(int fd, char *str)
{
  int i;
  i = 0;
  while (str[i])
    write(fd, &str[i++], 1);
  return (i);
}
int ft_execute(t_micro *sh, char **av, char **env)
{
  av[sh->i] = NULL;
  dup2(sh->tmp_fd, 0);
  close(sh->tmp_fd);
  execve(av[0], av, env);
  fd_putstr(2, "error: cannot execute ");
  fd_putstr(2, av[0]);
  fd_putstr(2, "\n");
  return (E_EXIT);
}
void  is_cd(t_micro *sh, char **av)
{
  if (sh->i != 2)
    fd_putstr(2, "error: cd: bad arguments\n");
  else if (chdir(av[1]) == ERROR)
  {
    fd_putstr(2, "error: cd: cannot directory to ");
    fd_putstr(2, av[1]);
    fd_putstr(2, "\n");
  }
}
int no_pipe(t_micro *sh, char **av, char **env)
{
  sh->pid = fork();
  if (sh->pid == ERROR)
    return (E_EXIT);
  if (!sh->pid)
  {
    if (ft_execute(sh, av, env))
      return (E_EXIT);
  }
  else
  {
    close(sh->tmp_fd);
    while (sh->n_p-- > 0 )
      waitpid(-1, NULL, WUNTRACED);
    sh->tmp_fd = dup(0);
  }
  return (EXIT_SUCCESS);
}
int is_pipe(t_micro *sh, char **av, char **env)
{
  sh->n_p++;
  pipe(sh->fd);
  sh->pid = fork();
  if (sh->pid == ERROR)
    return (E_EXIT);
  if (!sh->pid)
  {
    close(sh->fd[0]);
    dup2(sh->fd[1], 1);
  if (ft_execute(sh,av, env))
      return (E_EXIT);
  }
  else
  {
    close(sh->fd[1]);
    close(sh->tmp_fd);
    sh->tmp_fd = sh->fd[0];
  }
  return (EXIT_SUCCESS);
}
int main(int ac, char **av, char **env)
{
  t_micro sh;
  (void)ac;
  sh.i = 0;
  sh.tmp_fd = dup(0);
  sh.n_p = 1;
  while (av[sh.i] && av[sh.i + 1])
  {
    av = &av[sh.i + 1];
    sh.i = 0;
    while (av[sh.i] && strcmp(av[sh.i], ";") && strcmp(av[sh.i], "|"))
      sh.i++;
    if (av[0] && !strcmp(av[0], "cd"))
      is_cd(&sh, av);
    else if (sh.i && (!av[sh.i] || !strcmp(av[sh.i], ";")))
    {
      if (no_pipe(&sh, av, env))
        return (E_EXIT);
    }
    else if (sh.i && !strcmp(av[sh.i], "|"))
    {
      if (is_pipe(&sh, av, env))
        return (E_EXIT);
    }
  }
  close(sh.tmp_fd);
  return (EXIT_SUCCESS);
}
