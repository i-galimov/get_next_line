#include "get_next_line.h"

size_t	ft_strlen(char *result)
{
	int	i;

	if (result == NULL)
		return (0);
	i = 0;
	while (result[i])
		i++;
	return (i);
}

void	ft_join(char *str, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;

	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!str)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	ft_join(str, s1, s2);
	free(s1);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	if (s == NULL)
		return (NULL);
	i = 0;
	str = (char *)s;
	while (str[i] != (char)c && str[i])
		i++;
	if (str[i] == (char)c)
		return (&str[i]);
	return (NULL);
}
