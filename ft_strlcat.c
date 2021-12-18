/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:43:46 by ayajirob          #+#    #+#             */
/*   Updated: 2021/12/18 13:13:36 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
