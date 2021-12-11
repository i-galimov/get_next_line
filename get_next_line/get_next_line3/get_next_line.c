#include "get_next_line.h"

char	*ft_last_str(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!s)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		s[j++] = str[i++];
	s[j] = '\0';
	free(str);
	return (s);
}

char	*ft_get_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read_str(int fd, char *str)
{
	char	*line;
	int		i;

	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	i = 1;
	while (i != 0 && !ft_strchr(str, '\n'))
	{
		i = read(fd, line, BUFFER_SIZE);
		if (i == -1)
		{
			free(line);
			return (NULL);
		}
		line[i] = '\0';
		str = ft_strjoin(str, line);
	}
	free(line);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = ft_read_str(fd, str);
	if (!str)
		return (NULL);
	line = ft_get_line(str);
	str = ft_last_str(str);
	return (line);
}
