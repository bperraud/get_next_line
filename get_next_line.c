/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:22:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/02/18 19:42:13 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include "stdio.h"
#include "fcntl.h"

int main()
{
	//int fd = open("get_next_line.h", O_RDONLY);
	int fd = open("gnlTester/files/get_next_line.h", O_RDONLY);
	char *str;

	while ((str = get_next_line(fd)))
	{
		printf("%s", str);
		free(str);
	}
	printf("%s", str);
	free(str);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE > 1000000000)
		return (NULL);
	else
		return (true_gnl(fd));
}

char	*true_gnl(int fd)
{
	long			ret;
	static char		buff[BUFFER_SIZE + 1];
	char			*line;
	char			*temp;
	long			i;

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
	i = ret;
	while (i < BUFFER_SIZE + 1)
		buff[i++] = 0;
	return (true_gnl_2(ret, line, buff, temp));
}

char	*true_gnl_2(long ret, char *line, char *buff, char *temp)
{
	if (ret == -1 || ret == 0)
	{
		if (ret == 0 && line[0] != '\0')
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
			while (ret--)
				*buff++ = 0;
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
	if (split)
	{
		//printf("len of split : %d", ft_strlen(split));
		//free(split);

		//printf("split 0: %s\n", split[0]);
		//printf("split 1: %s\n", split[1]);

		free(split[0]);
		free(split[1]);
		free(split);
	}
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
