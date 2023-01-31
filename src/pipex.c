/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:12:02 by hzaz              #+#    #+#             */
/*   Updated: 2023/02/01 00:03:06 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

//size_t	ft_ultimate_len(char **s)
//{
//	size_t	len;
//	int		i;
//	int		j;

//	len = 0;
//	i = 0;
//	j = 0;
//	while (s && s[i] && s[i][j])
//	{
//		while (s && s[i][j++])
//			len++;
//		i++;
//		j = 0;
//	}
//	return (len);
//}

//char	**read_file(const char	*path)
//{
//	int		i;
//	int		j;
//	int		fd;
//	char	**ret;

//	i = 0;
//	j = 0;
//	fd = open(path, O_RDONLY);
//	while (get_next_line(fd))
//		i++;
//	ret = malloc(sizeof(char *) * ++i);
//	if (!ret)
//		return (NULL);
//	ret[i] = NULL;
//	close(fd);
//	fd = open(path, O_RDONLY);
//	return (NULL);
//	while (j < i)
//		ret[j++] = get_next_line(fd);
//	return (ret);
//}

//char	*file_tochar(char **file)
//{
//	size_t	len;
//	size_t	i;
//	char	*str;

//	i = 0;
//	len = ft_ultimate_len(file);
//	str = malloc(sizeof(char) *(len + 1));
//	if (!str)
//		return (NULL);
//	str[len] = '\0';
//	while (i < len && file && *file)
//	{
//		while (**file && *file && file)
//			str[i++] = (*(*file)++);
//		(*file)++;
//	}
//	return (str);
//	free(file);
//}

int	erreur(char c)
{
	if (c == 'm')
	{
		perror("fork Error");
		return (-1);
	}
	if (c == 'o')
	{
		perror("fork Error");
		exit(EXIT_FAILURE);
		return (-1);
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
				//printf("\n%s\n", envp[i]);
				if (envp[i][j] == ':')
					if (access(ret, F_OK) == 0)
					{
						execve(ret, f, envp);
					}

			}
		}

	}


}

void	process_p(char	**av, char **envp,int *fd)
{
	int	outf;
	outf = open(av[4], O_WRONLY, 0777);

	if (outf < 0)
		erreur('o');

	dup2(fd[0], STDIN_FILENO);
	dup2(outf, STDOUT_FILENO);
	close(fd[1]);
	exec_cmd(envp, av[3]);
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
