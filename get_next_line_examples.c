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

include "get_next_line.h"

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
