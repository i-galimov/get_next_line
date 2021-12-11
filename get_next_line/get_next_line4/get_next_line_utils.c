#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	char	*dest;
	char	*s;

	dest = (char *)dst;
	s = (char *)src;
	if (dstsize > 0)
	{
		i = 0;
		while (i < dstsize - 1)
		{
			if (s[i] == '\0')
				break ;
			dest[i] = s[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(s));
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;
	int		lenght;

	str = (char *)s1;
	lenght = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (lenght + 1));
	if (str == NULL)
		return (0);
	i = 0;
	while (i < lenght)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*str;
	size_t	i;
	size_t	j;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	lenght;

	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	lenght = ft_strlen(s + start);
	if (lenght < len)
		len = lenght;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!(ptr))
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}
