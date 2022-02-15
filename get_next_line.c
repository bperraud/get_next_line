/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:22:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/02/15 16:23:26 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	i = BUFFER_SIZE + 1;
	while (i > ret - 1)
		buff[i--] = 0;
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
