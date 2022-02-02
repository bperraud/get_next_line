/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:23:43 by bperraud          #+#    #+#             */
/*   Updated: 2022/02/02 17:36:05 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//# define BUFFER_SIZE 5

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char    *ft_strncpy(char *dest, const char *src, unsigned int n);
char	**ft_split(char const *s, const char c);
size_t  ft_strlen(const char *s);
char	*ft_strdup(const char *s1);

#endif