/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:12:02 by hzaz              #+#    #+#             */
/*   Updated: 2023/03/16 00:13:54 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"


int	erreur(char c)
{
	if (c == 'a')
	{
		perror("Usage: infile cmd1 cmd2  outfile\n");
		return (1);
	}
	if (c == 'm')
	{
		perror("fork Error");
		exit(EXIT_FAILURE);
		return (1);
	}
	return (0);
}

void	exec_cmd( char *envp[], char *cmd)
{
	int		i;
	int		j;
	int		k;
	char	*ret;
	char	**f;

	j = 0;
	i = -1;
	f = ft_split(cmd, ' ');
	f[0] = ft_strjoin("/",f[0]);
	while (envp[++i] != NULL && envp)
	{
		ret = ft_substr(envp[i], 0, 5);
		if (ft_same_str(ret, "PATH=", 5) == 1)
		{
			j = 5;

			while (envp[i][j] && envp[i][++j] != '\0' && envp)
			{
				k = j;
				while (envp[i][j] != ':' && envp[i][j] && envp)
					j++;
				ret = ft_strjoin_free1(ft_substr(envp[i], k, ((j) - k)), f[0]);

				if (envp[i][j] == ':')
					if (access(ret, F_OK) == 0)
						execve(ret, f, envp);

			}
		}
	}
	ft_ulti_double_free(&f, ret);
}

void	process_p(char	**av, char **envp,int *fd)
{
	int	outf;
	outf = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0777);

	if (outf < 0)
		erreur('o');

	dup2(fd[0], STDIN_FILENO);
	dup2(outf, STDOUT_FILENO);
	close(fd[1]);
	exec_cmd(envp, av[3]);
	close(outf);
}

void	process_c(char	**av, char **envp,int *fd)
{
	int	inf;
	inf = open(av[1], O_RDONLY, 0777);
	if (inf < 0)
		erreur('o');
	dup2(inf, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	exec_cmd(envp, av[2]);
	close(inf);
}


int	main(int ac, char *av[], char *envp[])
{
	pid_t	pid;
	int	fd[2];

	if (ac != 5)
		return(erreur('a'));

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return(erreur('m'));
	else if (pid == 0)
		process_c(av, envp, fd);
	wait(NULL);
	process_p(av, envp, fd);
}
