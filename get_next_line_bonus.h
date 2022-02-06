/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:32:14 by bperraud          #+#    #+#             */
/*   Updated: 2022/02/06 15:32:14 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

char	*get_next_line(int fd);
char	*get_next_line_2(int ret, char *line, char *buff, char *temp);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char    *ft_strncpy(char *dest, const char *src, unsigned int n);
char	**ft_split(char const *s, const char c);
size_t  ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*end_of_line(char *buff, char *line);
void	ft_bzero(void *s, size_t n);

#endif