#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		k;
	char	*result;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	result = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 2);
	if (!result)
		return (NULL);
	k = 0;
	i = 0;
	while (s1[k])
		result[i++] = s1[k++];
	k = 0;
	while (s2[k])
		result[i++] = s2[k++];
	result[i] = '\0';
	free(s1);
	return (result);
}

char	*ft_strchr(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\n')
	{
		if (!s[i])
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
}

char	*cut_line(char *remain)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!remain[i])
		return (0);
	while (remain[i] && remain[i] != '\n')
		i++;
	tmp = (char *) malloc(sizeof(char) * (i + 2));
	if (!tmp)
		return (0);
	i = 0;
	while (remain[i] && remain[i] != '\n')
	{
		tmp[i] = remain[i];
		i++;
	}
	if (remain[i] == '\n')
	{
		tmp[i] = remain[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*cut_remain(char *remain)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (remain[i] && remain[i] != '\n')
		i++;
	if (!remain[i])
	{
		free(remain);
		return (0);
	}
	tmp = (char *) malloc(sizeof(char) * (ft_strlen(remain) - i + 1));
	if (!tmp)
		return (0);
	j = 0;
	i++;
	while (remain[i])
		tmp[j++] = remain[i++];
	tmp[j] = '\0';
	free(remain);
	return (tmp);
}

char	*fd_reader(int fd, char *remain)
{
	char	*buff;
	int		read_bytes;

	read_bytes = 1;
	buff = (char *) malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	while (read_bytes && !ft_strchr(remain))
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		remain = ft_strjoin(remain, buff);
	}
	free(buff);
	return (remain);
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*remain;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remain = fd_reader(fd, remain);
	if (!remain)
		return (NULL);
	result = cut_line(remain);
	remain = cut_remain(remain);
	return (result);
}
