#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *left_str, char *buff);
char	*last_step(char *string);
char	*get_line(char *string);
char	*read_to_string(int fd, char *string);
char	*get_next_line(int fd);

#endif
