/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 20:25:38 by ayajirob@st       #+#    #+#             */
/*   Updated: 2021/12/16 20:38:38 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

void	ft_error_processing(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

char	*ft_parsing(int argc, char **argv, int *process_num, int *cmd_index)
{
	char	*stop_value;

	if (argc < 5)
	{
		ft_putstr_fd("The number of arguments should be at least 4\n", 2);
		exit(EXIT_FAILURE);
	}
	*cmd_index = 2;
	*process_num = argc - 3;
	stop_value = NULL;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		*cmd_index = 3;
		*process_num = argc - 4;
		stop_value = ft_strjoin(argv[2], "\n");
		if (stop_value == NULL)
			ft_error_processing("Malloc failed for stop_value");
	}
	return (stop_value);
}

char	***ft_parsing_cmd(int process_num, int cmd_index, char **argv, int argc)
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

void	ft_parsing_path(int cmd_index, char ***array, char **path, int argc)
{
	int	y;

	y = 0;
	while (cmd_index < argc - 1)
	{
		path[y] = ft_strjoin("/usr/bin/", *array[y]);
		if (path[y] == NULL)
			ft_error_processing("Malloc failed for path");
		if (access(path[y], F_OK) == -1)
		{
			free(path[y]);
			path[y] = NULL;
			path[y] = ft_strjoin("/bin/", *array[y]);
			if (path[y] == NULL)
				ft_error_processing("Malloc failed for path");
			if (access(path[y], F_OK) == -1)
				ft_error_processing("Access failed");
		}
		cmd_index++;
		y++;
	}
}

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

void	ft_create_child(int proc_num, int **pipes, char **path, char ***cmd_arr)
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
				ft_error_processing("Execve failed");
			if (close(pipes[i][0] == -1) || close(pipes[i + 1][1] == -1))
				ft_error_processing("Close failed");
			exit(EXIT_SUCCESS);
		}
		cmd_arr++;
		path++;
		i++;
	}
}

void	ft_read_in_loop(int in_fd, int out_fd, char *stop_val)
{
	char	*s;
	int		stop_flag;

	stop_flag = 1;
	s = malloc(1);
	while (s && stop_flag)
	{
		free(s);
		s = NULL;
		s = get_next_line(in_fd);
		if (stop_val == NULL && s != NULL)
		{
			if (write(out_fd, s, ft_strlen(s)) == -1)
				ft_error_processing("Write failed");
		}
		else if (stop_val != NULL && ft_strncmp(s, stop_val, ft_strlen(s) != 0))
		{
			if (write(out_fd, s, ft_strlen(s)) == -1)
				ft_error_processing("Write failed");
		}
		else if (stop_val != NULL && ft_strncmp(s, stop_val, ft_strlen(s) == 0))
			stop_flag = 0;
	}
	if (close(in_fd) == -1 || close(out_fd) == -1)
		ft_error_processing("Close failed");
}

void	ft_read_input(char *infile, int first_pipe, char *stop_value)
{
	int	input_fd;

	if (stop_value != NULL)
		input_fd = 0;
	else
		input_fd = open(infile, O_RDONLY);
	if (input_fd == -1)
		ft_error_processing("");
	ft_read_in_loop(input_fd, first_pipe, stop_value);
}

void	ft_write_output(char *outfile, int last_pipe, char *stop_value)
{
	int	output_fd;

	if (stop_value != NULL)
	{
		output_fd = open(outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
		free(stop_value);
		stop_value = NULL;
	}
	else
		output_fd = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (output_fd == -1)
		ft_error_processing("");
	ft_read_in_loop(last_pipe, output_fd, NULL);
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
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	char	*stop_value;
	int		**pipes;
	char	**path;
	char	***cmd_array;
	int		cmd_index;
	int		process_num;

	stop_value = ft_parsing(argc, argv, &process_num, &cmd_index);
	cmd_array = ft_parsing_cmd(process_num, cmd_index, argv, argc);
	path = ft_memory_alloc_path(process_num);
	ft_parsing_path(cmd_index, cmd_array, path, argc);
	pipes = ft_create_pipes(process_num);
	ft_create_child(process_num, pipes, path, cmd_array);
	ft_close_unused_pipes_parent(pipes, process_num);
	ft_read_input(argv[1], pipes[0][1], stop_value);
	ft_write_output(argv[argc - 1], pipes[process_num][0], stop_value);
	ft_waiting_childs(process_num);
}
