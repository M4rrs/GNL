#include "get_next_line.h"

//finds length of a string
size_t	ft_strlen(const char	*s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

//joins two strings
char	*ft_strjoin(char const	*s1, char const	*s2)
{
	char	*str;
	char	*final;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	final = str;
	if (!str)
		return (NULL);
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (final);
}

// allocates mem, creates a substring based on starting length and end length.
char *ft_substr(char const	*s, unsigned int start, size_t	len)
{
	unsigned int	i;
	char			*str;

	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < len)
		str[i++] = s[start++];
	str[i] = 0;
	return (str);
}

//looks for a char in a string,
//returns pointer.
char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s) && s[i])
	{
		if (s[i] == c)
			return ((char *)(s + i));
		s++;
	}
	return (0);
}

//allocates sized mem, fills with 0
char	*ft_bzero(size_t size)
{
	char	*res;
	size_t	i;

	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (0);
	i = 0;
	while (i < size + 1)
	{
		*(char *)(res + i) = 0;
		i++;
	}
	return (res);
}
