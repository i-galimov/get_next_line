
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	ans;

	ans = 0;
	while (s[ans])
		ans++;
	return (ans);
}

char	*ft_strdup(const char *s)
{
	size_t			s_len;
	char			*new_str;
	size_t			i;

	s_len = ft_strlen(s);
	if (!(new_str = (char*)malloc(s_len + 1)))
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[s_len] = '\0';
	return (new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			i;
	size_t			s_len;

	if (!(substr = malloc(len + 1)))
		return (NULL);
	*substr = '\0';
	if (start >= ft_strlen(s))
		return (substr);
	i = 0;
	s_len = ft_strlen(s);
	while (i < len && i < s_len)
	{
		substr[i] = *(s + start + i);
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char*)s;
	while (*str || !c)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	char			*ans;
	unsigned int	total_len;

	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	total_len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = malloc(total_len + 1)))
		return (NULL);
	ans = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (ans);
}

static int	join_line_and_save(char **line, char **save)
{
	char	*tmp;
	char	*newline_ptr;

	if ((newline_ptr = ft_strchr(*save, '\n')))
	{
		tmp = *line;
		*line = ft_substr(*save, 0, newline_ptr - *save);
		free(tmp);
		if (!(*line))
			return (ERROR);
		tmp = *save;
		*save = ft_substr(newline_ptr + 1, 0, ft_strlen(newline_ptr + 1));
		free(tmp);
		if (!(*save))
			return (ERROR);
		return (SUCCESS);
	}
	else
	{
		tmp = *line;
		*line = *save;
		*save = NULL;
		free(tmp);
		return (CONTINUE_READ);
	}
}

static int	split_by_newline(char **line, char **save, char *buf)
{
	char	*old_line;
	char	*tmp;
	char	*newline_ptr;

	newline_ptr = ft_strchr(buf, '\n');
	if (!(tmp = ft_substr(buf, 0, newline_ptr - buf)))
		return (ERROR);
	old_line = *line;
	*line = ft_strjoin(*line, tmp);
	free(old_line);
	free(tmp);
	if (!(*line))
		return (ERROR);
	if (!(*save = ft_substr(newline_ptr + 1, 0,
								ft_strlen(newline_ptr + 1))))
		return (ERROR);
	return (SUCCESS);
}

static int	join_line_and_buf(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);
	if (!(*line))
		return (ERROR);
	return (CONTINUE_READ);
}

static int	read_process(int fd, char **line, char **save)
{
	ssize_t		read_size;
	int			ret;
	char		*buf;

	ret = CONTINUE_READ;
	if (!(buf = malloc(BUFFER_SIZE + 1)))
		return (ERROR);
	while (ret == CONTINUE_READ && (read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		if (ft_strchr(buf, '\n'))
			ret = split_by_newline(line, save, buf);
		else
			ret = join_line_and_buf(line, buf);
	}
	free(buf);
	if (ret == CONTINUE_READ && read_size == 0)
		ret = END_OF_FILE;
	else if (ret == CONTINUE_READ && read_size == -1)
		ret = ERROR;
	return (ret);
}

int			get_next_line(int fd, char **line)
{
	int			ret;
	static char	*save;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || !(*line = ft_strdup("")))
		return (ERROR);
	ret = CONTINUE_READ;
	if (save)
		ret = join_line_and_save(line, &save);
	if (ret == CONTINUE_READ)
		ret = read_process(fd, line, &save);
	return (ret);
}
