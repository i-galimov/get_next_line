/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaribel <amaribel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 04:10:11 by amaribel          #+#    #+#             */
/*   Updated: 2021/11/19 02:46:21 by amaribel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strncpy(char *dst, char *src, int dstsize)
{	
	int	i;

	i = 0;
	if (dstsize == 0)
		return (dst);
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;
	int		z;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == 0)
	{
		free (s1);
		return (0);
	}
	i = 0;
	j = 0;
	z = 0;
	while (s1 && s1[i])
		dest[z++] = s1[i++];
	while (s2[j])
		dest[z++] = s2[j++];
	dest[z] = '\0';
	free (s1);
	return (dest);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c && s[i])
		i++;
	if (s[i] == (char)c)
		return (s + i);
	else
		return (0);
}
