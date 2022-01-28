/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:04:39 by bperraud          #+#    #+#             */
/*   Updated: 2022/01/28 17:42:36 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

size_t	ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*cs;
	unsigned char		uc;

	cs = s;
	uc = c;
	while (n && *cs != uc)
	{
		n--;
		cs++;
	}
	if (n)
		return ((void *) cs);
	else
		return (NULL);
}

static char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	str = malloc((lens1 + lens2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strncpy(str, s1, lens1);
	ft_strncpy(str + lens1, s2, ft_strlen(s2));
	return (str);
}

static int	ft_wordlen(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	ft_wordcount(const char *str, char c)
{
	int	i;
	int	nbr_word;

	nbr_word = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		i = ft_wordlen(str, c);
		str += i;
		if (i)
			nbr_word++;
	}
	return (nbr_word);
}

static char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	*free_word(char **dest, int nbr_word)
{
	while (nbr_word--)
		free(dest[nbr_word]);
	free(dest);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		nbr_word;
	int		i;
	int		word_len;

	if (!s)
		return (NULL);
	nbr_word = ft_wordcount(s, c);
	dest = malloc((nbr_word + 1) * sizeof(char *));
	if (!dest)
		return (free_word(dest, 0));
	i = 0;
	while (i < nbr_word)
	{
		while (*s && *s == c)
			s++;
		word_len = ft_wordlen(s, c);
		dest[i] = malloc((word_len + 1) * sizeof(char));
		if (!dest[i])
			return (free_word(dest, i + 1));
		ft_strncpy(dest[i++], s, word_len);
		s += word_len;
	}
	dest[nbr_word] = NULL;
	return (dest);
}

