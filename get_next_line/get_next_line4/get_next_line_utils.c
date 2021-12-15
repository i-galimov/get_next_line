#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		k;
	char	*result;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	result = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 2);
	if (!result)
		return (NULL);
	k = 0;
	i = 0;
	while (s1[k])
		result[i++] = s1[k++];
	k = 0;
	while (s2[k])
		result[i++] = s2[k++];
	result[i] = '\0';
	free(s1);
	return (result);
}

char	*ft_strchr(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\n')
	{
		if (!s[i])
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
}
