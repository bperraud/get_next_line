/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:22:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/02/02 17:44:40 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

# include <fcntl.h>
# include "stdio.h"

/*
int main()
{
	int	fd;
	
	fd = open("file.txt", O_RDONLY);
	
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}
*/

char	*get_next_line(int fd)
{	
	int				ret;
	static char		buff[BUFFER_SIZE];
	char			*line;
	char			*temp;
	char			**split;

	ret = BUFFER_SIZE;
	line = ft_strdup("");
	while (ret == BUFFER_SIZE && ft_memchr(buff, '\n', BUFFER_SIZE) == NULL) // on lit au moins 1 octet
	{
		temp = line;
		line = ft_strjoin(line, buff);
		free(temp);
		ret = read(fd, buff, BUFFER_SIZE);		// continue a lire
	}
	if (ret == -1)	// erreur de read, free ?
		return (NULL);
	else if (ret == BUFFER_SIZE)	// fin de ligne  
	{
		split = ft_split(buff, '\n');		// enlever de line + stocker la fin du read apres le \n
		line = ft_strjoin(line, split[0]);
		ft_strncpy(buff, split[1], BUFFER_SIZE);
		free(split[0]);
		free(split[1]);
		free(split);
	}
	else // fin du fichier = pas de '\n'	/ vraiment utile ? avant d'avoir ret == 0 le fichier a deja été lu en entier 
	{
		buff[ret] = '\0';
		line = ft_strjoin(line, buff);
		return (line);
	}
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