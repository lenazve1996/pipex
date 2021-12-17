/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 20:02:20 by ayajirob@st       #+#    #+#             */
/*   Updated: 2021/12/17 20:02:43 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**ft_create_pipes(int process_num)
{
	int	i;
	int	**pipes;

	pipes = (int **)malloc((process_num + 1) * sizeof(int *));
	if (pipes == NULL)
		ft_error_processing("Malloc failed for pipes");
	i = 0;
	while (i < process_num + 1)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (pipe(pipes[i]) == -1)
			ft_error_processing("Pipe failed");
		i++;
	}
	return (pipes);
}

void	ft_close_unused_pipes_child(int i, int **pipes, int process_num)
{
	int	j;

	j = 0;
	while (j < process_num + 1)
	{
		if (i != j)
		{
			if (close(pipes[j][0]) == -1)
				ft_error_processing("Close failed");
		}
		if (i + 1 != j)
		{
			if (close(pipes[j][1]) == -1)
				ft_error_processing("Close failed");
		}
		j++;
	}
}

void	ft_close_unused_pipes_parent(int **pipes, int process_num)
{
	int	j;

	j = 0;
	while (j < process_num + 1)
	{
		if (j != process_num)
		{
			if (close(pipes[j][0]) == -1)
				ft_error_processing("Close failed");
		}
		if (j != 0)
		{
			if (close(pipes[j][1]) == -1)
				ft_error_processing("Close failed");
		}
		j++;
	}
}
