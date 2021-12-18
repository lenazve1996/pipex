/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:44:01 by ayajirob          #+#    #+#             */
/*   Updated: 2021/12/18 13:14:31 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	n;
	size_t			len_s;

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
	{
		substr[n++] = s[start++];
	}
	substr[n] = '\0';
	return (substr);
}
