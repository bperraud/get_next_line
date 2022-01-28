/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:22:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/01/28 17:56:53 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static const BUFFER_SIZE;

char	*get_next_line(int fd)
{	
	int				ret;
	char			temp[BUFFER_SIZE];
	char			*line;
	char			**split;
	static	char*	next_line;

	ret = read(fd, temp, BUFFER_SIZE);
	while (ret > 0 && ft_memchr(temp, '\n', BUFFER_SIZE) == NULL) // on lit au moins 1 octet
	{
		// free avant chaque join 
		line = ft_strjoin(line, temp);
		ret = read(fd, temp, BUFFER_SIZE);		// continue a lire
	}
	if (ret == -1)	// erreur de read, free ?
		return (NULL);
	else if (ret == 0) // fin du fichier 	
	{

	}
	else	// fin de ligne  
	{
		// enlever de line + stocker la fin du read apres le \n
		split = ft_split(temp, '\n');
		// il faut rajouter le '\n'
		line = ft_strjoin(line, split[0]);
		next_line = split[1];

	}

	return (line);
}
