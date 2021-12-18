/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 18:48:58 by ayajirob          #+#    #+#             */
/*   Updated: 2021/12/18 17:05:04 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>

# ifndef	BUFFER_SIZE
#  define	BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_substr_free(char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
int		ft_strchr_int(const char *s, int c);
char	*ft_reading(char *buffer, int fd);
char	*ft_filling_line(char **buf, int fd, int index);

#endif
