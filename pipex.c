#include "libft.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int	**ft_create_pipes(int process_num, int **pipes)
{
	int i;

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

void	ft_read_in_loop(int in_fd, int out_fd, int here_doc, char *stop_value)
{
	char	*line;
	int		stop_flag;

	stop_flag = 1;
	line = malloc(1);
	//printf("%s\n", stop_flag);
	while (line && stop_flag)
	{
		free(line);
		line = NULL;
		line = get_next_line(in_fd);
		printf("%d\n",ft_strncmp(line, stop_value, ft_strlen(line)));
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

int main(int argc, char **argv)
{
	int **pipes;
	int i;
	int x;
	int y;
	int n;
	int process_num;
	int pids[argc - 3];
	char	**path;
	char	***cmd_array;
	char	***array;
	int 	input_fd;
	int 	output_fd;
	int 	here_doc;
	char	*stop_value;

	if (argc < 5)
	{
		ft_putstr_fd("The number of arguments should be at least 4\n", 2);
		exit(EXIT_FAILURE);
	}
	here_doc = 0;
	x = 2;
	process_num = argc - 3;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		printf("It's here_doc\n");
		here_doc = 1;
		x = 3;
		process_num = argc - 4;
		stop_value = ft_strjoin(argv[2], "\n");
	}
	array = (char ***)malloc(process_num * sizeof(char **));
	path = (char **)malloc((process_num) * sizeof(char *));
	pipes = (int **)malloc((process_num + 1) * sizeof(int *));
	cmd_array = array;
	y = 0;
	while(x < argc - 1)
	{
		array[y] = ft_split(argv[x], ' ');
		path[y] = ft_strjoin("/usr/bin/", *array[y]);
		if (access(path[y], F_OK) == -1)
		{
			free(path[y]);
			path[y] = NULL;
			path[y] = ft_strjoin("/bin/", *array[y]);
			if (access(path[y], F_OK) == -1)
			{
				perror("Access failed");
				return (0);
			}
		}
		x++;
		y++;
	}
	printf("%s\n", path[0]);
	printf("%s\n", path[1]);
	//printf("%s\n", path[2]);
	printf("%s\n", cmd_array[0][0]);
	printf("%s\n", cmd_array[0][1]);
	printf("%s\n", cmd_array[1][0]);
	printf("%s\n", cmd_array[1][1]);
	//printf("%s\n", cmd_array[2][0]);
	//printf("%s\n", cmd_array[2][1]);
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
			dup2(pipes[i+1][1], 1);
			n = execve(*path, *cmd_array, (void *)0);
			if (n == -1)
			{
				perror("Execve failed");
				exit(EXIT_FAILURE);
			}
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			return (0);
		}
		cmd_array++;
		path++;
		i++;
	}
	ft_close_unused_pipes(i, pipes, process_num, 'p');
	if (here_doc == 1)
	{
		input_fd = 0;
	}
	else
		input_fd = open(argv[1], O_RDONLY);
	if (input_fd == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	ft_read_in_loop(input_fd, pipes[0][1], here_doc, stop_value);

	if (here_doc == 1)
	{
		output_fd = open(argv[argc-1], O_RDWR | O_APPEND | O_CREAT, 0644);
		here_doc = 0;
	}
	else
		output_fd = open(argv[argc-1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	ft_read_in_loop(pipes[process_num][0], output_fd, here_doc, argv[2]);

	i = 0;
	while (i < process_num)
	{
		wait(NULL);
		i++;
	}
	return(0);
}