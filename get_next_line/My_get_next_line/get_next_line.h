#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_save_nextstr(char *str);
char	*ft_get_line(char *str);
char	*ft_read_line(int fd, char *str);
char	*get_next_line(int fd);

#endif
