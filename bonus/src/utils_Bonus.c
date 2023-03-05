/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 03:46:47 by hzaz              #+#    #+#             */
/*   Updated: 2023/03/05 03:47:57 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	erreur(char c)
{
	if (c == 'e')
		perror("Exec failur");
	if (c == 'p')
		perror("Pipe failur");
	if (c == 'm')
	{
		perror("malloc failur");
		exit(EXIT_FAILURE);
	}
	if (c == 'a')
		perror("Usage: infile cmd1 cmd2 ... cmdn outfile\n");
	if (c == 'o')
		perror("Open Error");
	if (c == 'f')
	{
		perror("fork Error");
		exit(EXIT_FAILURE);
	}
	return (1);
}

char	**parse_cmd(char *cmd)
{
	char	**f;

	f = ft_split(cmd, ' ');
	if (!f)
		erreur('m');
	f[0] = ft_strjoin("/", f[0]);
	if (!f)
		erreur('m');
	return (f);
}
