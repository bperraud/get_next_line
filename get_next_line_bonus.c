/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:33:29 by bperraud          #+#    #+#             */
/*   Updated: 2022/02/06 15:33:29 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	else
		return (true_gnl(fd));
}

char	*true_gnl(int fd)
{
	long			ret;
	static char		buff[OPEN_MAX][BUFFER_SIZE + 1];
	char			*line;
	char			*temp;
	long			i;

	ret = BUFFER_SIZE;
	line = malloc(1 * sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (ret == BUFFER_SIZE && ft_memchr(buff[fd], '\n', BUFFER_SIZE) == NULL)
	{
		temp = line;
		line = ft_strjoin(line, buff[fd]);
		free(temp);
		ret = read(fd, buff[fd], BUFFER_SIZE);
	}
	temp = line;
	i = ret;
	while (i < BUFFER_SIZE + 1)
		buff[fd][i++] = 0;
	return (true_gnl_2(ret, line, buff[fd], temp));
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
	if (split)
	{
		line = ft_strjoin(line, split[0]);
		ft_strncpy(buff, split[1], BUFFER_SIZE);
		free(split[0]);
		free(split[1]);
		free(split);
		return (line);
	}
	else
		return (NULL);
}
