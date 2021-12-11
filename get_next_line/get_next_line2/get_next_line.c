#include "get_next_line.h"

char	*ft_buf_read(char *buffer, int fd)
{
	char	*line;
	int		ret;

	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	ret = 1;
	while (!(ft_strchr(buffer, '\n')) && ret != 0)
	{
		ret = read(fd, line, BUFFER_SIZE);
		if (ret == -1)
		{
			free(line);
			return (NULL);
		}
		line[ret] = '\0';
		buffer = ft_strjoin(buffer, line);
	}
	free(line);
	return (buffer);
}

char	*ft_find_line(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (buffer[0] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = -1;
	while (buffer[++i] && buffer[i] != '\n')
		line[i] = buffer[i];
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_save_str(char *buffer)
{
	char	*newline;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	newline = malloc(ft_strlen(buffer) - i + 1);
	if (!newline)
		return (NULL);
	i++;
	while (buffer[i])
		newline[j++] = buffer[i++];
	newline[j] = '\0';
	free(buffer);
	return (newline);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = ft_buf_read(buffer, fd);
	if (!buffer)
		return (NULL);
	line = ft_find_line(buffer);
	buffer = ft_save_str(buffer);
	return (line);
}
