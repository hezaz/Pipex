/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:12:02 by hzaz              #+#    #+#             */
/*   Updated: 2022/09/01 01:22:32 by hzaz             ###   ########.fr       */
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

char	*path_cmd( char *envp[])
{
	int		i;
	int		j;
	char	*ret;

	j = 0;
	i = 0;
	while (envp[i] && envp)
	{
		if (envp[i][0] == 'P')
			if (envp[i][1] == 'A')
				if (envp[i][2] == 'T')
					if (envp[i][3] == 'H' )
						if (++j)
							break ;
		printf("\nvoila:  %s\n",envp[++i]);
	}
	if (j)
		printf("\noui\n");
	else
		printf("\nnon\n");
	return (ret);
}

int	main(int ac, char *av[], char *envp[])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	char *ret = path_cmd(envp);
}
