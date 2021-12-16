#include "libft.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

char	*ft_parsing(int argc, char **argv, int *here_doc, int *process_num, int *cmd_index)
{
	char	*stop_value;

	if (argc < 5)
	{
		ft_putstr_fd("The number of arguments should be at least 4\n", 2);
		exit(EXIT_FAILURE);
	}
	*here_doc = 0;
	*cmd_index = 2;
	*process_num = argc - 3;
	stop_value = NULL;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		*here_doc = 1;
		*cmd_index = 3;
		*process_num = argc - 4;
		stop_value = ft_strjoin(argv[2], "\n");
	}
	return (stop_value);
}

void	ft_cmd_parser(int cmd_index, char ***array, char **path, int argc, char **argv)
{
	int	y;

	y = 0;
	while (cmd_index < argc - 1)
	{
		array[y] = ft_split(argv[cmd_index], ' ');
		if (array[y] == NULL)
			perror("Malloc failed: ");
		path[y] = ft_strjoin("/usr/bin/", *array[y]);
		if (path[y] == NULL)
			perror("Malloc failed: ");
		if (access(path[y], F_OK) == -1)
		{
			free(path[y]);
			path[y] = NULL;
			path[y] = ft_strjoin("/bin/", *array[y]);
			if (path[y] == NULL)
				perror("Malloc failed: ");
			if (access(path[y], F_OK) == -1)
				perror("Access failed");
		}
		cmd_index++;
		y++;
	}
}

int	**ft_create_pipes(int process_num, int **pipes)
{
	int	i;

	i = 0;
	while (i < process_num + 1)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (pipe(pipes[i]) == -1)
		{
			perror("Pipe failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipes);
}

void	ft_close_unused_pipes(int i, int **pipes, int process_num, char c)
{
	int	j;

	j = 0;
	if (c == 'c')
	{
		while (j < process_num + 1)
		{
			if (i != j)
				close(pipes[j][0]);
			if (i + 1 != j)
				close(pipes[j][1]);
			j++;
		}
	}
	else if (c == 'p')
	{
		while (j < process_num + 1)
		{
			if (j != process_num)
				close(pipes[j][0]);
			if (j != 0)
				close(pipes[j][1]);
			j++;
		}
	}
}

void ft_read_in_loop(int in_fd, int out_fd, int here_doc, char *stop_value)
{
	char *line;
	int stop_flag;

	stop_flag = 1;
	line = malloc(1);
	while (line && stop_flag)
	{
		free(line);
		line = NULL;
		line = get_next_line(in_fd);
		if (here_doc == 0 && line != NULL)
		{
			if (write(out_fd, line, ft_strlen(line)) == -1)
			{
				perror("Write failed");
				exit(EXIT_FAILURE);
			}
		}
		else if (here_doc == 1 && (ft_strncmp(line, stop_value, ft_strlen(line)) != 0))
		{
			if (write(out_fd, line, ft_strlen(line)) == -1)
			{
				perror("Write failed");
				exit(EXIT_FAILURE);
			}
		}
		else if (here_doc == 1 && (ft_strncmp(line, stop_value, ft_strlen(line)) == 0))
			stop_flag = 0;
	}
	if (close(in_fd) == -1)
		perror("Close failed");
	if (close(out_fd) == -1)
		perror("Close failed");
}

void	ft_read_input(int here_doc, char *infile, int first_pipe, char *stop_value)
{
	int	input_fd;

	if (here_doc == 1)
		input_fd = 0;
	else
		input_fd = open(infile, O_RDONLY);
	if (input_fd == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	ft_read_in_loop(input_fd, first_pipe, here_doc, stop_value);
}

void	ft_write_output(int here_doc, char *outfile, int last_pipe)
{
	int	output_fd;

	if (here_doc == 1)
	{
		output_fd = open(outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
		here_doc = 0;
	}
	else
		output_fd = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (output_fd == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	ft_read_in_loop(last_pipe, output_fd, here_doc, NULL);
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

int main(int argc, char **argv)
{
	int		**pipes;
	int		i;
	int		cmd_index;
	int		process_num;
	int		pids[argc - 3];
	char	**path;
	char	***cmd_array;
	char	***array;
	int		here_doc;
	char	*stop_value;

	stop_value = ft_parsing(argc, argv, &here_doc, &process_num, &cmd_index);
	array = (char ***)malloc(process_num * sizeof(char **));
	if (array == NULL)
		perror("Malloc failed: ");
	path = (char **)malloc((process_num) * sizeof(char *));
	if (path == NULL)
		perror("Malloc failed: ");
	pipes = (int **)malloc((process_num + 1) * sizeof(int *));
	if (pipes == NULL)
		perror("Malloc failed: ");
	cmd_array = array;
	ft_cmd_parser(cmd_index, array, path, argc, argv);
	pipes = ft_create_pipes(process_num, pipes);
	i = 0;
	while (i < process_num)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{
			ft_close_unused_pipes(i, pipes, process_num, 'c');
			dup2(pipes[i][0], 0);
			dup2(pipes[i + 1][1], 1);
			if (execve(*path, *cmd_array, (void *)0) == -1)
			{
				perror("Execve failed");
				exit(EXIT_FAILURE);
			}
			close(pipes[i][0]);
			close(pipes[i++ + 1][1]);
			exit(EXIT_SUCCESS);
		}
		cmd_array++;
		path++;
		i++;
	}
	ft_close_unused_pipes(i, pipes, process_num, 'p');
	ft_read_input(here_doc, argv[1], pipes[0][1], stop_value);
	ft_write_output(here_doc, argv[argc - 1], pipes[process_num][0]);
	ft_waiting_childs(process_num);
}
