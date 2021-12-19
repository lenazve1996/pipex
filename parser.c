/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 20:00:09 by ayajirob@st       #+#    #+#             */
/*   Updated: 2021/12/19 18:39:07 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

void	ft_parsing(int argc, int *process_num, int *cmd_index)
{
	if (argc < 5)
	{
		ft_putstr_fd("The number of arguments should be at least 4\n", 2);
		exit(EXIT_FAILURE);
	}
	*cmd_index = 2;
	*process_num = argc - 3;
}

char	***ft_parse_cmd(int process_num, int cmd_index, char **argv, int argc)
{
	char	***cmd_array;
	int		y;

	cmd_array = (char ***)malloc(process_num * sizeof(char **));
	if (cmd_array == NULL)
		ft_error_processing("Malloc failed for cmd_array");
	y = 0;
	while (cmd_index < argc - 1)
	{
		cmd_array[y] = ft_split(argv[cmd_index], ' ');
		if (cmd_array[y] == NULL)
			ft_error_processing("Malloc failed for cmd_array");
		cmd_index++;
		y++;
	}
	return (cmd_array);
}

char	**ft_memory_alloc_path(int process_num)
{
	char	**path;

	path = (char **)malloc((process_num) * sizeof(char *));
	if (path == NULL)
		ft_error_processing("Malloc failed for path");
	return (path);
}

void	ft_parsing_path(char ***array, char **path, int process_num)
{
	int	y;

	y = -1;
	while (++y < process_num)
	{
		if (array[y][0] == '\0')
			ft_putstr_fd("None of the arguments should be empty\n", 2);
		if (access(*array[y], F_OK) == -1)
		{
			path[y] = ft_strjoin("/usr/bin/", *array[y]);
			if (path[y] == NULL)
				ft_error_processing("Malloc failed for path");
			if (access(path[y], F_OK) == -1)
			{
				free(path[y]);
				path[y] = ft_strjoin("/bin/", *array[y]);
				if (path[y] == NULL)
					ft_error_processing("Malloc failed for path");
				if (access(path[y], F_OK) == -1)
					perror("Command not found");
			}
		}
		else
			path[y] = ft_substr(*array[y], 0, ft_strlen(*array[y]));
	}
}
