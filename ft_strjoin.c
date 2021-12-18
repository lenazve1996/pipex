/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:43:45 by ayajirob          #+#    #+#             */
/*   Updated: 2021/12/18 13:13:34 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		s2_size;
	int		s1_size;

	s2_size = ft_strlen(s2);
	s1_size = ft_strlen(s1);
	new_str = (char *)malloc((s2_size + s1_size + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_size + 1);
	ft_strlcat(new_str, s2, s2_size + s1_size + 1);
	return (new_str);
}
