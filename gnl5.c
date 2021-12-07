#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ('\0' == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
	return (str);
}

char	*last_step(char *string)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (string[i] && string[i] != '\n')
		i++;
	if (!string[i])
	{
		free(string);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(string) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (string[i])
		str[j++] = string[i++];
	str[j] = '\0';
	free(string);
	return (str);
}

char	*get_line(char *string)
{
	char	*line;
	int		i;

	i = 0;
	if (!string[i])
		return (NULL);
	while (string[i] && string[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (string[i] && string[i] != '\n')
	{
		line[i] = string[i];
		i++;
	}
	if (string[i] == '\n')
	{
		line[i] = string[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_to_string(int fd, char *string)
{
	char	*line;
	int		i;

	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	i = 1;
	while (i != 0 && !ft_strchr(string, '\n'))
	{
		i = read(fd, line, BUFFER_SIZE);
		if (i == -1)
		{
			free(line);
			return (NULL);
		}
		line[i] = '\0';
		string = ft_strjoin(string, line);
	}
	free(line);
	return (string);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*string;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	string = read_to_string(fd, string);
	if (!string)
		return (NULL);
	line = get_line(string);
	string = last_step(string);
	return (line);
}
/*
int	main()
{
	int fd;
	char *line;
	
	fd = open("/Users/fstupar/getnextline/42.txt", O_RDONLY);
	
	line = get_next_line(fd);
	printf("%s%s","Risultato finale: ", line);
	line = get_next_line(fd);
	printf("%s%s","Risultato finale: ", line);
	line = get_next_line(fd);
	printf("%s%s","Risultato finale: ", line);
	line = get_next_line(fd);
	printf("%s%s","Risultato finale: ", line);
	line = get_next_line(fd);
	printf("%s%s","Risultato finale: ", line);
	line = get_next_line(fd);
	printf("%s%s","Risultato finale: ", line);
}*/
