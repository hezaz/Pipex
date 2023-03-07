/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:46:17 by hzaz              #+#    #+#             */
/*   Updated: 2023/03/06 14:31:19 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	exec_cmd(char **envp, char **f)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	j = 0;
	i = -1;
	while (envp[++i] != NULL && envp)
	{
		ret = ft_substr(envp[i], 0, 5);
		j = 5;
		if (ft_same_str(ret, "PATH=", 5) == 1)
		{
			while (envp[i][j] && envp[i][++j] != '\0' && envp)
			{
				k = j;
				while (envp[i][j] != ':' && envp[i][j] && envp)
					j++;
				ret = ft_strjoin_free1(ft_substr(envp[i], k, (j - k)), f[0]);
				if (envp[i][j] == ':')
					if (access(ret, F_OK) == 0)
						execve(ret, f, envp);
			}
		}
	}
}

void	in_process(int tab[3], int fd[2], int argc)
{
	int	prevfd;

	if (tab[2] == 2)
	{
		close(fd[0]);
		dup2(tab[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	else if (tab[2] == argc - 2)
	{
		close(
			fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(tab[1], STDOUT_FILENO);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		prevfd = open("/dev/fd/0", O_RDONLY);
		dup2(prevfd, STDIN_FILENO);
		close(prevfd);
	}
}

void	process(int tab[3], int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
		erreur('p');
	pid = fork();
	if (pid < 0)
		erreur('f');
	else if (pid == 0)
	{
		in_process(tab, fd, argc);
		exec_cmd(envp, parse_cmd(argv[tab[2]]));
		erreur('e');
	}
	close(fd[1]);
	tab[0] = fd[0];
}

int	main(int argc, char *argv[], char **envp)
{
	int	infd;
	int	outfd;
	int	tab[3];
	int	i;
	int	status;

	i = 1;
	if (argc < 5)
		return (erreur('a'));
	infd = open(argv[1], O_RDONLY);
	outfd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfd < 0 || infd < 0)
		return (erreur('o'));
	tab[0] = infd;
	tab[1] = outfd;
	while (++i < argc - 1)
	{
		tab[2] = i;
		process(tab, argc, argv, envp);
	}
	wait(&status);
	return (0);
}

//int	main(int ac, char *av[], char *envp[])
//{
//	int		fd[2];
//	pid_t	pid;

//	if (ac < 5)
//		return (1);
//	if (pipe(fd) == -1)
//		return (1);
//	pid = fork();
//	if (pid == -1)
//		return (1);
//	else if (pid == 0)
//	{
//		dup2(fd[1], STDOUT_FILENO);
//		close(fd[0]);
//		process(&av[1], envp, NULL, fd);
//		exit(1);
//	}
//	dup2(fd[0], STDIN_FILENO);
//	close(fd[1]);
//	exec_cmd(envp, av[ac - 1]);
//	wait(NULL);
//	return (0);
//}