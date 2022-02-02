/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:22:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/02/02 01:26:58 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

# include <fcntl.h>
# include "stdio.h"

int main()
{
	int	fd;
	
	fd = open("file.txt", O_RDONLY);
	
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s", get_next_line(fd));
}

char	*get_next_line(int fd)
{	
	int				ret;
	char			buff[BUFFER_SIZE];
	char			*line;
	char			**split;
	static char 	save[BUFFER_SIZE];

	ft_strncpy(buff, save, BUFFER_SIZE);		// il ne peut pas avoir + de BUFFERSIZE element qui reste 
	ret = BUFFER_SIZE;
	line = "";	// pour le premier join 
	while (ret == BUFFER_SIZE && ft_memchr(buff, '\n', BUFFER_SIZE) == NULL) // on lit au moins 1 octet
	{
		// free avant chaque join 
		line = ft_strjoin(line, buff);
		ret = read(fd, buff, BUFFER_SIZE);		// continue a lire
	}
	if (ret == -1)	// erreur de read, free ?
		return (NULL);
	else if (ret == BUFFER_SIZE)	// fin de ligne  
	{
		split = ft_split(buff, '\n');		// enlever de line + stocker la fin du read apres le \n
		line = ft_strjoin(line, split[0]);
		ft_strncpy(save, split[1], BUFFER_SIZE);
	}
	else // fin du fichier = pas de '\n'	/ vraiment utile ? avant d'avoir ret == 0 le fichier a deja été lu en entier 
	{
		ft_strncpy(buff, buff, ret);
		line = ft_strjoin(line, buff);
		return (line);
	}
	return (line);
}
