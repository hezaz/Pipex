/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:12:02 by hzaz              #+#    #+#             */
/*   Updated: 2022/08/31 14:59:12 by hzaz             ###   ########.fr       */
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



int	main(int ac, char *av[], char *envp[])
{
	int	i,j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		printf("\n%s\n", envp[i]);
		i++;
	}
}
