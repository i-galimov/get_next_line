#include "get_next_line.h"

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
