#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

/*Trying to make it work, definitely does not follow normi. Yet.
Some comments are temp, leave me alone.*/
static int ft_read(int fd, char **buff, int *r)
{
	int	res;
	res = read(fd, *buff, BUFFER_SIZE);
	*r = res;
	return (res);
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
		free(*str);
		if (temp[0] != '\0')
			*str = temp; //str will now contain remainder of the string, along with the characters in the next round when re-run
		else
			free(temp);
	}
	//else //str unav, what do you do?
	else
	{
		res = ft_strdup(*str);
		free(*str);
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
	
	if (BUFFER_SIZE < 1)
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
		free(res);
		res = temp;
		if (ft_strchr(buff, '\n'))
			break;
	}
	 //everytime read is run, checks for a \n in buff. Stops the whole loop. ^
	free(buff);
	return (get_line(&res));
}

int	main()
{
    int fd = open("test.txt", O_RDONLY);
	printf("%s\n",get_next_line(fd));
	printf("\n second run ------------------------- \n");
	printf("%s\n",get_next_line(fd));
	printf("\n third run ------------------------- \n");
	printf("%s\n",get_next_line(fd));
}
