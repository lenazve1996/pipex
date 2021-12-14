/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob <ayajirob@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 18:45:45 by ayajirob          #+#    #+#             */
/*   Updated: 2021/12/04 19:16:13 by ayajirob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	int		n;
	char	*buf;

	len = ft_strlen(s1);
	buf = (char *)malloc(len + 1 * sizeof(char));
	n = 0;
	if (buf == NULL)
		return (NULL);
	while (n <= len)
	{
		buf[n] = s1[n];
		n++;
	}
	return (buf);
}

int	ft_strchr_int(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_reading(char *buffer, int fd)
{
	int	read_result;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	read_result = read(fd, buffer, BUFFER_SIZE);
	if (read_result <= 0 )
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer[read_result] = '\0';
	return (buffer);
}

char	*ft_filling_line(char **buf, int fd, int index)
{
	char	*line;

	if (index == -1)
	{
		line = ft_strdup(buf[fd]);
		free(buf[fd]);
		buf[fd] = NULL;
	}
	else
	{
		line = ft_substr_free(buf[fd], 0, index + 1);
		if ((index + 1) == (int)ft_strlen(buf[fd]))
		{
			free(buf[fd]);
			buf[fd] = NULL;
			return (line);
		}
		else
			buf[fd] = ft_substr_free(buf[fd], index + 1, ft_strlen(buf[fd]));
	}
	if (index == -1)
		line = ft_strjoin_free(line, get_next_line(fd));
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1025];
	char		*line;
	int			index;

	if (fd < 0)
		return (NULL);
	line = NULL;
	if (buffer[fd] == NULL)
		buffer[fd] = ft_reading(buffer[fd], fd);
	if (buffer[fd] == NULL)
		return (NULL);
	index = ft_strchr_int(buffer[fd], '\n');
	line = ft_filling_line(buffer, fd, index);
	return (line);
}
