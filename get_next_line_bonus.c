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
	int				ret;
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

char	*get_next_line_2(int ret, char *line, char *buff, char *temp)
{
	if (ret == -1 || ret == 0)	
	{
		if (line[0] != '\0')		
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
			ft_bzero(buff, BUFFER_SIZE + 1);
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

void	ft_bzero(void *s, size_t n)
{
	char	*us;

	us = s;
	while (n--)
		*us++ = 0;
}
