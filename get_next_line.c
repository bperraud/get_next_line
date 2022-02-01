/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:22:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/02/01 23:46:12 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

# include <fcntl.h>
# include "stdio.h"

int main()
{
	int	fd;
	
	fd = open("file.txt", O_RDONLY);
	
	printf("%s", get_next_line(fd));

}

char	*get_next_line(int fd)
{	
	int				ret;
	char			buff[BUFFER_SIZE];
	char			*line;
	char			**split;
	//static char*	next_line;

	ret = read(fd, buff, BUFFER_SIZE);
	//printf("%s\n", buff);
	line = "";

	//ft_strjoin(line, next_line);		// si il restait des caractères dans le buffer à l'appel précèdent il faut les rajouter
	while (ret > 0 && ft_memchr(buff, '\n', BUFFER_SIZE) == NULL) // on lit au moins 1 octet
	{
		// free avant chaque join 
		line = ft_strjoin(line, buff);
		ret = read(fd, buff, BUFFER_SIZE);		// continue a lire
	}
	if (ret == -1)	// erreur de read, free ?
		return (NULL);
	else if (ret == 0) // fin du fichier = pas de '\n'	
	{

	}
	else	// fin de ligne  
	{
		// enlever de line + stocker la fin du read apres le \n
		split = ft_split(buff);
		line = ft_strjoin(line, split[0]);
		//next_line = split[1];
	}
	return (line);
}
