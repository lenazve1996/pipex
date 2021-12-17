/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 20:05:18 by ayajirob@st       #+#    #+#             */
/*   Updated: 2021/12/17 20:05:37 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_read_in_loop(int in_fd, int out_fd, char *stop_val)
{
	char	*s;

	s = malloc(1);
	while (s)
	{
		s = ft_free_str(s);
		s = get_next_line(in_fd);
		if (stop_val == NULL && s != NULL)
		{
			if (write(out_fd, s, ft_strlen(s)) == -1)
				ft_error_processing("Write failed");
		}
		else if (stop_val != NULL && ft_strncmp(s, stop_val, ft_strlen(s)) != 0)
		{
			if (write(out_fd, s, ft_strlen(s)) == -1)
				ft_error_processing("Write failed");
		}
		else if (stop_val != NULL && ft_strncmp(s, stop_val, ft_strlen(s)) == 0)
			s = ft_free_str(s);
	}
	if ((close(in_fd) == -1) || (close(out_fd) == -1))
		ft_error_processing("Close failed");
}

void	ft_read_input(char *infile, int first_pipe, int cmd_index, char **argv)
{
	int		input_fd;
	char	*stop_value;

	if (cmd_index == 3)
	{
		input_fd = 0;
		stop_value = ft_strjoin(argv[2], "\n");
		if (stop_value == NULL)
			ft_error_processing("Malloc failed for stop_value");
	}
	else
	{
		input_fd = open(infile, O_RDONLY);
		stop_value = NULL;
	}
	if (input_fd == -1)
		ft_error_processing("");
	ft_read_in_loop(input_fd, first_pipe, stop_value);
	free(stop_value);
	stop_value = NULL;
}

void	ft_write_output(char *outfile, int last_pipe, int cmd_index)
{
	int	output_fd;

	if (cmd_index == 3)
		output_fd = open(outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		output_fd = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (output_fd == -1)
		ft_error_processing("");
	ft_read_in_loop(last_pipe, output_fd, NULL);
}
