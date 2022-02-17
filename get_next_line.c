#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

// allocates mem and duplicates the string.
static char	*ft_strdup(const char *s)
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

// reads from an fd,
// sets the number of bytes read to a ptr,
// data read is uploaded to the buffer
// Not really sure why calling read on its own in
// the main func didn't work
static int ft_read(int fd, char **buff, int *r)
{
	int	res;

	res = read(fd, *buff, BUFFER_SIZE);
	*r = res;
	return (res);
}

//because free doesn't automatically re-initialize to NULL,
// so it needs to be done manually.
// But free is used a few times in this code so having to 
// re-initialize NULL might take up more lines and then normi
// starts yelling at me
static void	ft_free(char **s)
{
	if (s)
	{
		free(*s);
		*s = NULL;
	}
}

//when last updated buffer contains a nl, this func will be called,
// loops through the buffer to find nl,
// trims the string from the start to the nl,
// remainder will be duplicated into temp, str is freed,
// and temp will be assigned to str, str now contains
// the remainder of the string, which will be updated for
//the next call.
static char	*get_line(char	**str)
{
	int	i;
	char	*temp;
	char	*res;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if((*str)[i])
	{
		res = ft_substr(*str, 0, i + 1);
		temp = ft_strdup(*str + i + 1);
		if (temp[0] != '\0')
			*str = temp;
		else
			ft_free(&temp);
	}
	else
	{
		res = ft_strdup(*str);
		ft_free(str);
	}
	return (res);
}
//ret 0 if invalid fd or buff size.
//ret 0 if malloc failed.
// stops reading when a nl is found.
//buff has read content, temp is where it is joined to res,
//and res is updated.

char *get_next_line(int fd)
{
	static char	*res;
	char	*buff;
	char	*temp;
	int	r;
	
	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (0);
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	while (ft_read(fd, &buff, &r) > 0)
	{
		buff[r] = 0;
		if (!res)
			res = ft_bzero(0);
		temp = ft_strjoin(res, buff);
		ft_free(&res);
		res = temp;
		if (ft_strchr(buff, '\n'))
			break;
	}
	ft_free(&buff);
	if (r < 0 || (r == 0 && !res))
		return (0);
	return (get_line(&res));
}

// int	main()
// {
//     int fd = open("test.txt", O_RDONLY);
// 	printf("%s\n",get_next_line(fd));
// 	// printf("\n second run ------------------------- \n");
// 	// printf("%s\n",get_next_line(fd));
// 	// printf("\n third run ------------------------- \n");
// 	// printf("%s\n",get_next_line(fd));
// }

// int main()
// {
// 	int fd;
// 	char *s;

// 	fd = 0;
// 	while ((s = get_next_line(fd)))
// 		printf("%s\n", s);
// }
