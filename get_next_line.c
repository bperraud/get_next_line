/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:22:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/02/06 16:50:07 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
int main()
{
	int	fd;
	char *str;
	//fd = open("gnlTester/files/empty", O_RDONLY);
	fd = open("gnlTester/files/43_with_nl", O_RDONLY);
	str = get_next_line(fd);	
	printf("%s", str);
	//free(str);
		
	char *str2 = get_next_line(fd);
	printf("%s", str2);
	//free(str2);
	char *str3 = get_next_line(fd);
	printf("%s", str3);
	//free(str3);
	char *str4 = get_next_line(fd);
	printf("%s", str4);
	//printf("\nchar : %c\n", str4[16]);
	//free(str4);
	char *str5 = get_next_line(fd);
	printf("%s", str5);
	//free(str5);
}
*/

char	*get_next_line(int fd)
{	
	long			ret;
	static char		buff[BUFFER_SIZE + 1];
	char			*line;
	char			*temp;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > FOPEN_MAX)
        return (NULL);
	ret = BUFFER_SIZE;
	line = ft_strdup("");
	while (ret == BUFFER_SIZE && ft_memchr(buff, '\n', BUFFER_SIZE) == NULL)
	{
		temp = line;
		line = ft_strjoin(line, buff);
		free(temp);
		ret = read(fd, buff, BUFFER_SIZE);	
	}
	temp = line;
	ft_bzero(buff + ret, BUFFER_SIZE + 1);
	return (get_next_line_2(ret, line, buff, temp));
}

char	*get_next_line_2(long ret, char *line, char *buff, char *temp)
{
	long	size;

	if (ret == -1 || ret == 0)	
	{
		if (ret == -1 && line[0] != '\0')
			return (line);
		free(temp);
		return (NULL);
	}
	else
	{			
		if (ft_memchr(buff, '\n', BUFFER_SIZE) != NULL)		
			line = end_of_line(line, buff);
		else	
		{
			line = ft_strjoin(line, buff);
			//ft_bzero(buff, BUFFER_SIZE + 1);
			size = BUFFER_SIZE + 1;
			while (size--)
				buff = 0;
		}
	}			
	free(temp);
	return (line);
}

char	*end_of_line(char *line, char *buff)
{
	char	**split;

	split = ft_split(buff, '\n');		
	line = ft_strjoin(line, split[0]);
	ft_strncpy(buff, split[1], BUFFER_SIZE);
	free(split[0]);
	free(split[1]);
	free(split);
	return (line);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;

	dest = malloc(((ft_strlen(s1)) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (dest[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_bzero(void *s, long n)
{
	char	*us;

	us = s;
	while (n--)
		*us++ = 0;
}
