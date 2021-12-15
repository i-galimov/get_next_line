#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_get_line(char **buff)
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

void	ft_read_buf(int fd, char **save)
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
		ft_read_buf(fd, &buff);                    // At first "BUFF" is declared as NULL.
	line = ft_get_line(&buff);                   // <-- We return the line with ft_return_line.
	return (line);
}

