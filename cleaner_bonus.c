/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 19:42:47 by ayajirob@st       #+#    #+#             */
/*   Updated: 2021/12/18 16:58:19 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_free_str(char *str)
{
	free(str);
	str = NULL;
	return (str);
}

static char	***ft_free_array_of_arrays(char ***cmd_array, int process_num)
{
	char	*tmp;
	int		i;
	int		y;

	y = 0;
	while (y < process_num)
	{
		i = 0;
		while (cmd_array[y][i] != NULL)
		{
			tmp = cmd_array[y][i];
			free(tmp);
			i++;
		}
		free(cmd_array[y]);
		y++;
	}
	free(cmd_array);
	return (cmd_array);
}

static void	ft_free_char_array(char **path, int process_num)
{
	int		i;

	i = 0;
	while (i < process_num)
	{
		free(path[i]);
		i++;
	}
	free(path);
}

static void	ft_free_int_array(int **pipes, int process_num)
{
	int	i;

	i = 0;
	while (i < process_num + 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

char	***ft_free_mem(char **path, int **pipes, int proc_num, char ***cmd_arr)
{
	ft_free_char_array(path, proc_num);
	ft_free_int_array(pipes, proc_num);
	cmd_arr = ft_free_array_of_arrays(cmd_arr, proc_num);
	return (cmd_arr);
}
