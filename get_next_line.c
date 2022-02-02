/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:22:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/02/02 23:52:16 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

# include <fcntl.h>
# include "stdio.h"


int main()
{
	int	fd;
	char *str;
	//fd = open("gnlTester/files/empty", O_RDONLY);
	fd = open("file.txt", O_RDONLY);

	str = get_next_line(fd);	
	while (str)
	{
		printf("%s", str);
		//free(str);
		str = get_next_line(fd);
	}
	free(str);
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
}

char	*get_next_line(int fd)
{	
	int				ret;
	static char		buff[BUFFER_SIZE + 1];
	char			*line;
	char			*temp;
	char			**split;
	//static char		*save;
	//free(save);
	if (fd < 0 || BUFFER_SIZE < 1 || fd >= FOPEN_MAX)
        return (NULL);
	ret = BUFFER_SIZE;
	line = ft_strdup("");
	while (ret == BUFFER_SIZE && ft_memchr(buff, '\n', BUFFER_SIZE) == NULL)
	{
		temp = line;
		line = ft_strjoin(line, buff);
		free(temp);
		ret = read(fd, buff, BUFFER_SIZE);		// continue a lire
	}
	
	temp = line;
	buff[ret] = '\0';

	if (ret == -1 || ret == 0)	// erreur de read ou fin de fichier (rien read)
	{
		free(temp);
		return (NULL);
	}
	else if (ret == BUFFER_SIZE)	// fin de ligne  
	{
		split = ft_split(buff, '\n');		// enlever de line + stocker la fin du read apres le \n
		line = ft_strjoin(line, split[0]);
		ft_strncpy(buff, split[1], BUFFER_SIZE);
		free(split[0]);
		free(split[1]);
		free(split);
	}
	else // fin fichier (ret < BUFFER_SIZE)
	{
		line = ft_strjoin(line, buff);
	}
	//save = line;
	free(temp);
	return (line);
}


static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;

	dest = malloc(((ft_strlen(s1)) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	return (ft_strcpy(dest, s1));
}