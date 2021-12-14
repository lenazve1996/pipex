#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int pipes[argc - 3 + 1][2];
	int i;
	int j;
	int x;
	int y;
	int n;
	int process_num;
	int pids[argc - 3];
	char	**cmd1;
	char	**cmd2;
	int 	input_fd;
	int 	output_fd;
	int 	new_out_fd;
	char	*line;
	char	buff[100];
	int		read_result;

	 if (argc < 5)
	{
		ft_putstr_fd("The number of arguments should be at least 4\n", 2);
		return (0);
	}
	process_num = argc - 3;
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	i = 0;
	while (i < process_num + 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("Pipe failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
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
			j = 0;
			while (j < process_num + 1)
			{
				if (i != j)
					close(pipes[j][0]);
				if (i + 1 != j)
					close(pipes[j][1]);
				j++;
			}
			dup2(pipes[i][0], 0);
			dup2(pipes[i+1][1], 1);
			n = execve("/usr/bin/wc", cmd1, (void *)0);
			if (n == -1)
				perror("Execve failed");
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			return (0);
		}
		i++;
	}
	j = 0;
	while (j < process_num + 1)
	{
		if (j != process_num)
			close(pipes[j][0]);
		if (j != 0)
			close(pipes[j][1]);
		j++;
	}

	input_fd = open("infile", O_RDONLY);
	line = malloc(1);
	while(line)
	{
		free(line);
		line = NULL;
		line = get_next_line(input_fd);
		if (line != NULL)
		{
			printf("Main process sent %s\n", line);
			if (write(pipes[0][1], line, ft_strlen(line)) == -1)
			{
				perror("Write failed");
				exit(EXIT_FAILURE);
			}
		}
	}
	if (close(pipes[0][1]) == -1)
		perror("Close failed");
	line = malloc(100);
	output_fd = open("outfile", O_RDWR | O_CREAT, 0777);
	if (read(pipes[process_num][0], line, 100) == -1)
	{
		perror("Main Read failed");
		exit(EXIT_FAILURE);
	}
	write(output_fd, line, ft_strlen(line));
	printf("Main recieved the final result. It is %s\n", line);
	close(output_fd);
	if (close(pipes[process_num][0]) == -1)
		perror("Close failed");
	i = 0;
	while (i < process_num)
	{
		wait(NULL);
		i++;
	}
	return(0);
}