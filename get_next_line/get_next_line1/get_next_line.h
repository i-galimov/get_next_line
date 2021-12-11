#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(char *result);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_change_str(char *res);
char	*ft_get_line(char *str);
char	*ft_get(char *str, int fd);
char	*get_next_line(int fd);

#endif
