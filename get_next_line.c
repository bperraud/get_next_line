/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:22:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/02/05 18:57:29 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

# include <fcntl.h>
# include "stdio.h"

/*
int main()
{
	int	fd;
	char *str;
	//fd = open("gnlTester/files/empty", O_RDONLY);
	fd = open("file.txt", O_RDONLY);

	str = get_next_line(fd);	
	printf("%s", str);
	free(str);
		
	char *str2 = get_next_line(fd);
	printf("%s", str2);
	free(str2);

	char *str3 = get_next_line(fd);
	printf("%s", str3);
	free(str3);

	char *str4 = get_next_line(fd);
	printf("%s", str4);
	//printf("\nchar : %c\n", str4[16]);
	free(str4);

	char *str5 = get_next_line(fd);
	printf("%s", str5);
	free(str5);
} */


char	*get_next_line(int fd)
{	
	int				ret;
	static char		buff[BUFFER_SIZE + 1];
	char			*line;
	char			*temp;

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
	//buff[ret] = '\0';

	ft_bzero(buff + ret , BUFFER_SIZE + 1 - ret );

	if (ret == -1 || ret == 0)	// erreur de read ou fin de fichier (plus rien à lire)
	{
		if (line[0] != '\0')		// si ret = 0 mais qu'il reste dans le buff
			return (line);
		free(temp);
		return (NULL);
	}
	else //if (ret < BUFFER_SIZE){
	{			// fin de ligne return split[0] save split[1], si fin de fichier, split ne change rien et return buff ? 
		
		if (ft_memchr(buff, '\n', BUFFER_SIZE) != NULL)		// fin de ligne -> split
		{
			line = end_of_line(line, buff);
		}
		else	// fin de fichier
		{
			//printf("line : %s\n", line);
			//printf("buff : %s\n", buff);
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

	split = ft_split(buff, '\n');		// enlever de line + stocker la fin du read apres le \n
	line = ft_strjoin(line, split[0]);
	ft_strncpy(buff, split[1], BUFFER_SIZE);
	free(split[0]);
	free(split[1]);
	free(split);
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

void	ft_bzero(void *s, size_t n)
{
	char	*us;

	us = s;
	while (n--)
		*us++ = 0;
}
