/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 20:25:38 by ayajirob@st       #+#    #+#             */
/*   Updated: 2021/12/18 17:27:10 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "get_next_line.h"

void	ft_error_processing(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_make_child(int proc_num, int **pipes, char **path, char ***cmd_arr)
{
	int	i;
	int	pid;

	i = 0;
	while (i < proc_num)
	{
		pid = fork();
		if (pid == -1)
			ft_error_processing("Fork failed");
		if (pid == 0)
		{
			ft_close_unused_pipes_child(i, pipes, proc_num);
			if (dup2(pipes[i][0], 0) == -1 || dup2(pipes[i + 1][1], 1) == -1)
				ft_error_processing("Dup2 failed");
			if (execve(*path, *cmd_arr, (void *)0) == -1)
			{
				if (close(pipes[i][0] == -1) || close(pipes[i + 1][1] == -1))
					ft_error_processing("Close failed");
				ft_error_processing("Execve failed");
			}
		}
		cmd_arr++;
		path++;
		i++;
	}
}

void	ft_waiting_childs(int process_num)
{
	int	i;

	i = 0;
	while (i < process_num)
	{
		wait(NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		**pipes;
	char	**path;
	char	***cmd_array;
	int		cmd_index;
	int		process_num;

	ft_parsing(argc, argv, &process_num, &cmd_index);
	cmd_array = ft_parse_cmd(process_num, cmd_index, argv, argc);
	path = ft_memory_alloc_path(process_num);
	ft_parsing_path(cmd_array, path, process_num);
	pipes = ft_create_pipes(process_num);
	ft_make_child(process_num, pipes, path, cmd_array);
	ft_close_unused_pipes_parent(pipes, process_num);
	ft_read_input(argv[1], pipes[0][1], cmd_index, argv);
	ft_write_output(argv[argc - 1], pipes[process_num][0], cmd_index);
	ft_waiting_childs(process_num);
	ft_free_mem(path, pipes, process_num, cmd_array);
	return (0);
}
