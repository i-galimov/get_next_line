#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)

{
	size_t	i;
	char	*dest;
	char	*s;

	dest = (char *)dst;
	s = (char *)src;
	if (dstsize > 0)
	{
		i = 0;
		while (i < dstsize - 1)
		{
			if (s[i] == '\0')
				break ;
			dest[i] = s[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(s));
}

size_t	ft_strlen(const char *s)

{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)

{
	char	*str;
	int		i;
	int		lenght;

	str = (char *)s1;
	lenght = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (lenght + 1));
	if (str == NULL)
		return (0);
	i = 0;
	while (i < lenght)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(const char *s1, const char *s2)

{
	size_t	len;
	char	*str;
	size_t	i;
	size_t	j;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)

{
	char	*ptr;
	size_t	lenght;

	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	lenght = ft_strlen(s + start);
	if (lenght < len)
		len = lenght;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!(ptr))
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}

char	*ft_strchr(const char *s, int c)

{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_return_line(char **buff)

{
	char	*line;
	char	*temp;
	int		i;

	if (!*buff || **buff == '\0')                   // We check if "buff" is empty or reach EOF, if so ..
	{
		free (*buff);                               // we free it ..
		*buff = NULL;
		return (NULL);                              // and return NULL.
	}
	i = 0;
	while ((*buff)[i] != '\n' && (*buff)[i] != 0)   // Otherwise we go through "buff" with our counter to find
		i++;                                        // new line or the end of "buff".
	if ((*buff)[i] == '\n')                         // If we found the new line ..
		i++;                                        // the counter will move to the next line and start reading the next time we call "buff".
	line = ft_substr(*buff, 0, i);                  // Then we substract the line from start to '\n' ..
	temp = ft_substr(*buff, i, ft_strlen(*buff));   // but keep in mind the lenght of the buff.
	free(*buff);                                    // Finally we can fill "buff" to "temp" and free "buff"
	*buff = temp;
	return (line);
}

void	ft_read_file(int fd, char **save)

{
	int		res;
	char	buff[BUFFER_SIZE + 1];
	char	*temp;

	if (BUFFER_SIZE < 0 || BUFFER_SIZE > 10000000)
		return ;
	res = read(fd, buff, BUFFER_SIZE);              // <-- In "res" we store what we first read.
	while (res > 0)                                 // <-- As soon as there is something to read (EOF)
	{
		buff[res] = '\0';                           // <-- The end of the buff string.
		if (!*save)
			temp = ft_strdup(buff);                 // <-- We store everything in temporary buff so we can
		else
			temp = ft_strjoin(*save, buff);
		free (*save);                               // <-- free "save" of all that remains and then
		*save = temp;                               // <-- put everything that we read into "temp"
		if (ft_strchr(*save, '\n'))                 // <-- We look for the next new line, if not ...
			return ;
		res = read(fd, buff, BUFFER_SIZE);          // <-- we keep reading until we find one.
	}
}

char	*get_next_line(int fd)

{
	static char	*buff = NULL;
	char		*line;

	if (BUFFER_SIZE < 0 || fd < 0 || BUFFER_SIZE > 10000000)
		return (NULL);
	if (!buff || !(ft_strchr(buff, '\n')))          // <-- We check if there is a new line in "BUFF" or if it's a NULL.
		ft_read_file(fd, &buff);                    // At first "BUFF" is declared as NULL.
	line = ft_return_line(&buff);                   // <-- We return the line with ft_return_line.
	return (line);
}

