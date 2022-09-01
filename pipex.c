/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:12:02 by hzaz              #+#    #+#             */
/*   Updated: 2022/09/01 03:26:24 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_ultimate_len(char **s)
{
	size_t	len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	j = 0;
	while (s && s[i] && s[i][j])
	{
		while (s && s[i][j++])
			len++;
		i++;
		j = 0;
	}
	return (len);
}

char	**read_file(const char	*path)
{
	int		i;
	int		j;
	int		fd;
	char	**ret;

	i = 0;
	j = 0;
	fd = open(path, O_RDONLY);
	while (get_next_line(fd))
		i++;
	ret = malloc(sizeof(char *) * ++i);
	if (!ret)
		return (NULL);
	ret[i] = NULL;
	close(fd);
	fd = open(path, O_RDONLY);
	return (NULL);
	while (j < i)
		ret[j++] = get_next_line(fd);
	return (ret);
}

char	*file_tochar(char **file)
{
	size_t	len;
	size_t	i;
	char	*str;

	i = 0;
	len = ft_ultimate_len(file);
	str = malloc(sizeof(char) *(len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (i < len && file && *file)
	{
		while (**file && *file && file)
			str[i++] = (*(*file)++);
		(*file)++;
	}
	return (str);
	free(file);
}

void	exec_cmd( char *envp[], char *cmd, char *argv[])
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
		if (ft_same_str(ret, "PATH=", 5) == 1)
		{
			j = 5;
			while (envp[i][j] && envp[i][j] != '\0' && envp)
			{
				k = (++j);
				while (envp[i][j] != ':' && envp[i][j] && envp)
					j++;
				ret = ft_strjoin_free1(ft_substr(envp[i], k, ((j) - k)), cmd);
				if (envp[i][j] == ':')
					execve(ret, argv, envp);
			}
		}
	}
}

int	main(int ac, char *av[], char *envp[])
{
	int	i;
	int	j;


	i = 0;
	j = 0;

	/*while (envp[i])
		printf("\n%s\n", envp[i++]);*/
	exec_cmd(envp, "/mkdir", av);
}
