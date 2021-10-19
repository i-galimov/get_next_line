// Example 0.

#include "get_next_line.h"

void	ft_strchr0(char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != (char)c && s[i] != 0)
		s++;
	if (s[i] == (char)c)
		s[i] = 0;
}

void	ft_strzero(char *input, int len)
{
	while (len--)
		input[len] = 0;
}

int		str_process(char *input, char **result)
{
	char		*tmp;
	char		*tmp2;

	if (ft_strrchr(input, '\n'))
	{
		tmp = ft_strdup(input);
		input = ft_strcpy(input, &ft_strchr(input, '\n')[1]);
		ft_strchr0(tmp, 10);
		tmp2 = *result;
		*result = ft_strjoin(*result, tmp);
		free(tmp);
		free(tmp2);
		return (1);
	}
	else
	{
		tmp = *result;
		*result = ft_strjoin(*result, input);
		free(tmp);
		ft_strzero(input, BUFF_SIZE);
		return (0);
	}
}

int		get_next_line(const int fd, char **line)
{
	static char	*buff[10000];
	int			ret;

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!buff[fd])
		buff[fd] = ft_strnew(BUFF_SIZE);
	*line = ft_strnew(0);
	if (*buff[fd])
		if (str_process(buff[fd], line))
			return (1);
	ft_strzero(buff[fd], BUFF_SIZE);
	while ((ret = read(fd, buff[fd], BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		if (str_process(buff[fd], line))
			return (1);
	}
	if (**line == 0)
		return (0);
	return (1);
}

// Example 1.

#include "get_next_line.h"

static void	next_line(char *str, char **line)
{
	size_t	i;
	char	*next_line;

	i = ft_strcspn(str, "\n");
	next_line = ft_strnew(i);
	ft_memcpy(next_line, str, i);
	line[0] = next_line;
}

static char	*remaining_lines(char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			i++;
			return (&str[i]);
		}
		i++;
	}
	return (&str[i]);
}

int			get_next_line(const int fd, char **line)
{
	int				ret;
	char			*tmp;
	char			buf[BUFF_SIZE + 1];
	static char		*file[MAX_FD];

	if (fd < 0 || fd > MAX_FD || !line)
		return (-1);
	if (!file[fd])
	{
		file[fd] = ft_strnew(0);
		while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[ret] = '\0';
			tmp = file[fd];
			file[fd] = ft_strjoin(tmp, buf);
			ft_strdel(&tmp);
		}
		if (ret == -1)
			return (-1);
	}
	if (file[fd][0] == '\0')
		return (0);
	next_line(file[fd], line);
	file[fd] = remaining_lines(file[fd]);
	return (1);
}

// Example 2.

# include "get_next_line.h"

int		ft_new_line(char **s, char **line, int fd, int ret)
{
	char	*tmp;
	int		len;

	len = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		len++;
	if (s[fd][len] == '\n')
	{
		*line = ft_strsub(s[fd], 0, len);
		tmp = ft_strdup(s[fd] + len + 1);
		free(s[fd]);
		s[fd] = tmp;
		if (s[fd][0] == '\0')
			ft_strdel(&s[fd]);
	}
	else if (s[fd][len] == '\0')
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*s[255];
	char		buf[BUFF_SIZE + 1];
	char		*tmp;
	int			ret;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strnew(1);
		tmp = ft_strjoin(s[fd], buf);
		free(s[fd]);
		s[fd] = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (s[fd] == NULL || s[fd][0] == '\0'))
		return (0);
	return (ft_new_line(s, line, fd, ret));
}

// Example 3.

#include "get_next_line.h"

/*
** This function appends a single line into our line variable. We do this by
** finding the length of the line. If at index len, the character is a newline,
** we save the string into line up to the length found. Then we readjust the
** stored data (**s) by creating a temporary string that stored the rest of data
** after the newline. We free the stored data to update it to the current
** address because we already append a line from it. This is done by freeing *s
** and setting it equal to the temporary string that stored the remaining data.
** At any point when we reach the end of the file, we free the memory used to
** track our location in *s because it is not needed anymore.
*/

static int	appendline(char **s, char **line)
{
	int		len;
	char	*tmp;

	len = 0;
	while ((*s)[len] != '\n' && (*s)[len] != '\0')
		len++;
	if ((*s)[len] == '\n')
	{
		*line = ft_strsub(*s, 0, len);
		tmp = ft_strdup(&((*s)[len + 1]));
		free(*s);
		*s = tmp;
		if ((*s)[0] == '\0')
			ft_strdel(s);
	}
	else
	{
		*line = ft_strdup(*s);
		ft_strdel(s);
	}
	return (1);
}

/*
** This is a helper function created to output the results after all the other
** cases are taken care of in get_next_line. For example, if ret is less than 0,
** then return -1 since an error occurred. If the reading is completed, return a
** 0. Else, go to appendline function to return 1 and save the line read at the
** current address of the static variable stored.
*/

static int	output(char **s, char **line, int ret, int fd)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && s[fd] == NULL)
		return (0);
	else
		return (appendline(&s[fd], line));
}

/*
** The get_next_line function reads a file and returns the line ending with a
** newline character from a file descriptor. A static variable is used, so that
** whenever get_next_line is called, it remembers the previous function call.
** When get_next_line is first called, we check to see if our static variable
** **s is empty. If it is, we allocate memory for it using our buff string.
** In the loop, we will continue to read more of the line and join them together
** using a temporary string. This temporary string will replace the stored data
** each iteration so that we can keep track of how much is read and delete
** the previous stored data. This is needed because we are only reading so many
** n-bytes at a time decided by our BUFF_SIZE. If we read at each iteration
** without freeing memory, then we would have memory leaks. The loop breaks when
** a newline is encountered. Finally, we call output function to check what
** should be returned.
*/

int			get_next_line(const int fd, char **line)
{
	int			ret;
	static char	*s[FD_SIZE];
	char		buff[BUFF_SIZE + 1];
	char		*tmp;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(s[fd], buff);
			free(s[fd]);
			s[fd] = tmp;
		}
		if (ft_strchr(s[fd], '\n'))
			break ;
	}
	return (output(s, line, ret, fd));
}


// Example 4. 

#include "get_next_line.h"

char	*get_save(char *save)
{
	char	*rtn;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!save)
		return (0);
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (0);
	}
	if (!(rtn = malloc(sizeof(char) * ((ft_strlen(save) - i) + 1))))
		return (0);
	i++;
	while (save[i])
		rtn[j++] = save[i++];
	rtn[j] = '\0';
	free(save);
	return (rtn);
}

char	*get_line(char *str)
{
	int		i;
	char	*rtn;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(rtn = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		rtn[i] = str[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

int		get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*save;
	int				reader;

	reader = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!has_return(save) && reader != 0)
	{
		if ((reader = read(fd, buff, BUFFER_SIZE)) == -1)
		{
			free(buff);
			return (-1);
		}
		buff[reader] = '\0';
		save = join_str(save, buff);
	}
	free(buff);
	*line = get_line(save);
	save = get_save(save);
	if (reader == 0)
		return (0);
	return (1);
}
