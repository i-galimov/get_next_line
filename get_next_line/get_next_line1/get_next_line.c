#include "get_next_line.h"

char	*ft_change_str(char *res)
{
	int		i;
	int		j;
	char	*new_res;

	i = 0;
	j = 0;
	while (res[i] != '\0' && res[i] != '\n')
		i++;
	if (res[i] == '\n')
		i++;
	if (res[i] == 0)
	{
		free (res);
		return (NULL);
	}
	new_res = (char *)malloc(sizeof(char) * (ft_strlen(res) - i + 1));
	if (!new_res)
		return (NULL);
	while (res[i] != '\0')
		new_res[j++] = res[i++];
	new_res[j] = 0;
	free(res);
	return (new_res);
}

char	*ft_get_line(char *str)
{
	int		len;
	char	*line;
	int		j;

	len = 0;
	j = 0;
	if (str[0] == '\0')
		return (NULL);
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	while (j < len)
	{
		line[j] = str[j];
		j++;
	}
	line[j] = 0;
	return (line);
}

char	*ft_get(char *str, int fd)
{
	char	*buffer;
	int		a;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	a = 1;
	while (1)
	{
		a = read(fd, buffer, BUFFER_SIZE);
		if (a == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[a] = 0;
		str = ft_strjoin(str, buffer);
		if (ft_strchr(str, '\n') != NULL || a == 0)
			break ;
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*res;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	res = ft_get(res, fd);
	if (res == NULL)
		return (NULL);
	line = ft_get_line(res);
	res = ft_change_str(res);
	return (line);
}
