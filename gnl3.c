#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len;
	size_t	length;
	size_t	i;
	size_t	j;

	if (s1 && s2)
	{
		i = 0;
		j = 0;
		len = ft_strlen(s1);
		length = ft_strlen(s2);
		if (!(result = (char *)malloc(sizeof(char) * (len + length + 1))))
			return (NULL);
		while (s1[i])
			result[j++] = s1[i++];
		i = 0;
		while (s2[i])
			result[j++] = s2[i++];
		result[j] = '\0';
		return (result);
	}
	return (NULL);
}

char		*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

char		*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*copy;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	if (!(copy = (char *)malloc(len + 1 * sizeof(char))))
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;
	unsigned int	j;

	if (!s)
		return (NULL);
	if (!*s || start > (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (!(substring = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (start == i)
		{
			while (j < len && s[i])
				substring[j++] = s[i++];
			substring[j] = '\0';
			return (substring);
		}
		i++;
	}
	return (NULL);
}

int			ft_free_memory(char **s, int fd, char **line)
{
	*line = ft_strdup("");
	free(s[fd]);
	s[fd] = NULL;
	return (0);
}

int			ft_move_line(char **s, int fd, char **line)
{
	char	*cup;
	int		i;

	i = 0;
	while (s[fd][i] != '\n' && s[fd][i] != '\0')
		i++;
	if (s[fd][i] == '\n')
	{
		*line = ft_substr(s[fd], 0, i);
		cup = ft_strdup(s[fd] + i + 1);
		free(s[fd]);
		s[fd] = cup;
	}
	else
	{
		*line = ft_strdup(s[fd]);
		free(s[fd]);
		s[fd] = NULL;
		return (0);
	}
	return (1);
}

int			get_next_line(int fd, char **line)
{
	char		*buffer;
	static char *s[4864];
	int			rder;
	char		*cup;

	if (line == NULL || fd > 4864 || fd < 0 || read(fd, s, 0) < 0)
		return (-1);
	if (!(buffer = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	if (!s[fd])
		s[fd] = ft_strdup("");
	while ((rder = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[rder] = '\0';
		cup = ft_strjoin(s[fd], buffer);
		free(s[fd]);
		s[fd] = cup;
		if (ft_strchr(s[fd], '\n'))
			break ;
	}
	free(buffer);
	if (rder == 0 && *s[fd] == '\0')
		return (ft_free_memory(s, fd, line));
	return (ft_move_line(s, fd, line));
}
