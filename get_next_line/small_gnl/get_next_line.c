/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaribel <amaribel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:24:33 by amaribel          #+#    #+#             */
/*   Updated: 2021/11/21 02:37:14 by amaribel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	change_buf_line(char	*buf, char	**line)
{
	char	*n;

	n = ft_strchr(buf, '\n');
	*n = '\0';
	*line = ft_strjoin(*line, buf);
	*line = ft_strjoin(*line, "\n");
	n++;
	ft_strncpy(buf, n, ft_strlen(n) + 1);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	long		count;

	if (read(fd, 0, 0) == -1 || BUFFER_SIZE < 0 || fd < 0)
		return (0);
	line = 0;
	count = 1;
	while ((ft_strchr(buf, '\n') == 0) && count > 0)
	{
		line = ft_strjoin(line, buf);
		count = read(fd, buf, BUFFER_SIZE);
		buf[count] = '\0';
	}
	if (count < 0 || (count == 0 && line[0] == '\0'))
	{
		free (line);
		return (0);
	}
	if (ft_strchr(buf, '\n'))
		change_buf_line(buf, &line);
	return (line);
}
