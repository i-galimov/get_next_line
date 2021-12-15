#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s);
char	*cut_line(char *remain);
char	*cut_remain(char *remain);
char	*fd_reader(int fd, char *remain);
char	*get_next_line(int fd);

#endif
