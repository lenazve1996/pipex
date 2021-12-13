/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob <ayajirob@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 18:48:01 by ayajirob          #+#    #+#             */
/*   Updated: 2021/12/04 19:16:35 by ayajirob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	if (!s)
		return (0);
	while (*s++ != '\0')
		length++;
	return (length);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_length;

	src_length = ft_strlen(src);
	if (dstsize != 0)
	{
		while (dstsize-- > 1 && *src)
		{
			*dst++ = *src++;
		}
		*dst = '\0';
	}
	return (src_length);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	l;
	size_t	m;

	l = 0;
	m = 0;
	while (dst[l] && l < dstsize)
	{
		l++;
	}
	while (src[m] && (l + m + 1) < dstsize)
	{
		dst[l + m] = src[m];
		m++;
	}
	if (l < dstsize)
	{
		dst[l + m] = '\0';
	}
	return (l + ft_strlen(src));
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_str;
	int		s2_size;
	int		s1_size;

	if (s2 == NULL)
		return ((char *)s1);
	s2_size = ft_strlen(s2);
	s1_size = ft_strlen(s1);
	new_str = (char *)malloc((s2_size + s1_size + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_size + 1);
	ft_strlcat(new_str, s2, s2_size + s1_size + 1);
	free(s1);
	s1 = NULL;
	free(s2);
	s2 = NULL;
	return (new_str);
}

char	*ft_substr_free(char *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	n;
	size_t			len_s;
	int				begin;

	begin = start;
	len_s = ft_strlen(s);
	if (start >= len_s)
		len = 0;
	else if (len_s - start < len)
		len = len_s - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	n = 0;
	if (substr == NULL)
		return (NULL);
	while (n < len && s[start])
		substr[n++] = s[start++];
	substr[n] = '\0';
	if (begin > 0)
	{
		free(s);
		s = NULL;
	}
	return (substr);
}
