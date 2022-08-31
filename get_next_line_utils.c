#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_dup(char *s1, size_t n)
{
	size_t	len;
	size_t	i;
	char	*dest;

	i = 0;
	len = ft_strlen(s1);
	if (n < len)
		len = n;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (dest && s1 && s1[i] && i < len)
	{
		dest[i] = s1[i];
		s1[i++] = '\0';
	}
	dest[i] = '\0';
	return (dest);
}

char	*gnl_join(char *tmp, char *buf)
{
	int		i;
	int		j;
	char	*ret;

	i = -1;
	j = -1;
	if ((!tmp && !*buf) || (!tmp && !buf))
		return (NULL);
	if ((tmp && !*buf) || (tmp && !buf))
		return (tmp);
	if ((!tmp && *buf) || (!*tmp && *buf))
		return (gnl_dup(buf, ft_strlen(buf)));
	ret = malloc(sizeof(char) * (ft_strlen(tmp) + ft_strlen(buf) + 1));
	if (!ret)
		return (NULL);
	while (tmp[++i])
		ret[i] = tmp[i];
	free(tmp);
	while (buf[++j])
	{
		ret[i++] = buf[j];
		buf[j] = '\0';
	}
	ret[i] = '\0';
	return (ret);
}

char	*find_line(char **tmp, char **buf)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (!*tmp && !*buf)
		return (NULL);
	*tmp = gnl_join(*tmp, *buf);
	while ((*tmp)[i] && (*tmp)[i] != '\n')
		i++;
	if ((*tmp)[i] != '\n')
		return (NULL);
	ret = gnl_dup(*tmp, ++i);
	if (!ret)
		return (NULL);
	while ((*tmp)[i] && j < BUFFER_SIZE)
		(*buf)[j++] = (*tmp)[i++];
	free(*tmp);
	return (ret);
}
