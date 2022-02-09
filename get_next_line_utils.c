#include "get_next_line.h"

size_t	ft_strlen(const char	*s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	i = 0;
	if (!dup)
		return (0);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

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
char	*ft_substr(char const	*s, unsigned int	start, size_t	len)
{
	unsigned int				i;
	char						*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	if (ft_strlen(s) < len)
		str = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (0);
	while (s[start + i] && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

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