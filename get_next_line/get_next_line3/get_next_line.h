#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *line, char *buff);
char	*ft_last_str(char *str);
char	*ft_get_line(char *str);
char	*ft_read_str(int fd, char *str);
char	*get_next_line(int fd);

#endif
