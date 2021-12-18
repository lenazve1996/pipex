/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 20:05:18 by ayajirob@st       #+#    #+#             */
/*   Updated: 2021/12/18 16:59:05 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

void	ft_read_in_loop(int in_fd, int out_fd)
{
	char	*s;

	s = malloc(1);
	while (s)
	{
		s = ft_free_str(s);
		s = get_next_line(in_fd);
		if (s != NULL)
		{
			if (write(out_fd, s, ft_strlen(s)) == -1)
				ft_error_processing("Write failed");
		}
	}
	if ((close(in_fd) == -1) || (close(out_fd) == -1))
		ft_error_processing("Close failed");
}

void	ft_read_input(char *infile, int first_pipe)
{
	int		input_fd;

	input_fd = open(infile, O_RDONLY);
	if (input_fd == -1)
		ft_error_processing("");
	ft_read_in_loop(input_fd, first_pipe);
}

void	ft_write_output(char *outfile, int last_pipe)
{
	int	output_fd;

	output_fd = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (output_fd == -1)
		ft_error_processing("");
	ft_read_in_loop(last_pipe, output_fd);
}
