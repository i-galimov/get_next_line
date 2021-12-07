#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char		*ft_strchr(const char *str, int c)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (str[i] == c)
		return ((char*)(str) + i);
	return (NULL);
}

char		*ft_strdup(const char *src)
{
	size_t	i;
	char	*src2;

	i = 0;
	while (src[i] != '\0')
		i++;
	src2 = (char*)malloc((i + 1) * sizeof(char));
	if (!src2)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		src2[i] = src[i];
		i++;
	}
	src2[i] = '\0';
	return (src2);
}

char		*ft_strljoin(char *s1, char *s2, size_t len)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	if ((join = (char*)malloc((len + 1) * sizeof(char))) == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && len--)
	{
		join[i] = s1[i];
		i++;
	}
	free(s1);
	s1 = NULL;
	j = 0;
	while (s2[j] && len--)
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

int					ft_clean(char **buffer, char **line)
{
	free(*line);
	*line = NULL;
	free(*buffer);
	*buffer = NULL;
	return (-1);
}

int					ft_record(char **buffer, char **line, int endbuffer)
{
	char			*end;
	char			*buffer_copy;

	(*buffer)[endbuffer] = '\0';
	end = ft_strchr(*buffer, '\n');
	if (end)
	{
		*line = ft_strljoin(*line, *buffer, ft_strlen(*line) + (end - *buffer));
		buffer_copy = *buffer;
		*buffer = ft_strdup(end + 1);
		free(buffer_copy);
		buffer_copy = NULL;
		if (*line == NULL || *buffer == NULL)
			return (ft_clean(buffer, line));
		return (1);
	}
	*line = ft_strljoin(*line, *buffer, ft_strlen(*line) + BUFFER_SIZE);
	if (*line == NULL)
		return (ft_clean(buffer, line));
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*buffer;
	int				endbuffer;
	int				flag;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || (*line = ft_strdup("")) == NULL)
		return (-1);
	if (buffer != NULL)
		if ((flag = ft_record(&buffer, line, ft_strlen(buffer))) != 0)
			return (flag);
	free(buffer);
	buffer = NULL;
	if ((buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
		return (ft_clean(&buffer, line));
	if (read(fd, buffer, 0) < 0)
		return (ft_clean(&buffer, line));
	while ((endbuffer = read(fd, buffer, BUFFER_SIZE)) > 0)
		if ((flag = ft_record(&buffer, line, endbuffer)) != 0)
			return (flag);
	free(buffer);
	buffer = NULL;
	return (0);
}
