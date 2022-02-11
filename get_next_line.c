#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

/*Trying to make it work, definitely does not follow normi. Yet.
Some comments are temp, leave me alone.*/

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

static int ft_read(int fd, char **buff, int *r)
{
	int	res;
	res = read(fd, *buff, BUFFER_SIZE);
	*r = res;
	return (res);
}

static void	ft_free(char **s)
{
	if (s)
	{
		free(*s);
		*s = NULL;
	}
}

static char	*get_line(char	**str)
{
	int	i;
	char	*temp;
	char	*res;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if((*str)[i]) //str avail
	{
		res = ft_substr(*str, 0, i + 1); //creates substring of the line to return from start to \n
		temp = ft_strdup(*str + i + 1); // duplicates the remainder of the string
		ft_free(str);
		if (temp[0] != '\0')
			*str = temp; //str will now contain remainder of the string, along with the characters in the next round when re-run
		else
			ft_free(&temp);
	}
	//else //str unav, what do you do?
	else
	{
		res = ft_strdup(*str);
		ft_free(str);
	}
	return (res);
}
//ret 0 if fd is unavail or buffer invalid?
char *get_next_line(int fd)
{
	static char	*res;
	char	*buff;
	char	*temp;
	int	r;
	
	if (fd < 1 || fd > 1024 || BUFFER_SIZE < 1)
		return (0);
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (0); //malloc fail

	while (ft_read(fd, &buff, &r) > 0)
	{
		buff[r] = 0; //r basically points to the end of the arr, so allocate \0
		if (!res)
			res = ft_bzero(0);
			//res = 0;
		temp = ft_strjoin(res, buff);
		ft_free(&res);
		res = temp;
		if (ft_strchr(buff, '\n'))
			break;
	}
	 //everytime read is run, checks for a \n in buff. Stops the whole loop. ^
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
