#include "get_next_line.h"

char	*ft_get_read(int fd, char *str, char *buf)
{
	int	count;

	count = 1;
	while (!ft_strchr(str, '\n') && count)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count < 0)
		{
			free(buf);
			return (0);
		}
		buf[count] = '\0';
		if (!str)
			str = ft_substr(buf, 0, count);
		else
			str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*ft_get_end(char *str)
{
	char	*res;
	int		len;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	res = ft_substr(str, 0, len);
	return (res);
}

char	*ft_get_start(char *str)
{
	int		start;
	char	*res;

	start = 0;
	while (str[start] && str[start] != '\n')
		start++;
	start++;
	ret = ft_substr(str, start, ft_strlen(str));
	free(str);
	return (res);
}

char	*get_next_line(int fd)
{
	char		*res;
	char		*buf;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	str = ft_get_read(fd, str, buf);
	if (!str || str[0] == '\0')
	{
		free(str);
		str = 0;
		return (NULL);
	}
	res = ft_get_end(str);
	if (res[0] == '\0' || !res)
	{
		free(res);
		return (0);
	}
	str = ft_get_start(str);
	return (res);
}
