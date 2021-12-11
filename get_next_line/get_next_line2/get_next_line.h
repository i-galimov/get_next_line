#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(char *str);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *line, char *buffer);
char	*buffread(char *buffer, int fd);
char	*find_line(char *buffer);
char	*save_leftovers(char *buffer);
char	*get_next_line(int fd);

#endif
