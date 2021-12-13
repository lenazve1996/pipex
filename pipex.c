#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

#define PROCESS_NUM 3

int main(int argc, char **argv)
{
	int pipes[PROCESS_NUM + 1][2];
	int i;
	int j;
	int x;
	int y;
	int n;
	int pids[PROCESS_NUM];
	char	**cmd1;
	int input_fd;
	int output_fd;
	int new_out_fd;
	char	*line;
	char	buff[100];
	int		read_result;

	
	// if (argc < 5)
	//{
	//	ft_putstr_fd("The number of arguments should be at least 4\n", 2);
	//	return (0);
	// }

	i = 0;
	while (i < PROCESS_NUM + 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("Pipe failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < PROCESS_NUM)
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
			while (j < PROCESS_NUM + 1)
			{
				if (i != j)
					close(pipes[j][0]);
				if (i + 1 != j)
					close(pipes[j][1]);
				j++;
			}
			line = malloc(1);
			dup2(pipes[i][0], 0);
			//while (line != NULL)
			//{
			//	free(line);
			//	line = NULL;
			//	line = get_next_line(pipes[i][0]);
			//	printf("(%d) read %s", i, line);
			//	//write(1, line, ft_strlen(line));
			//	if (write(pipes[i + 1][1], line, ft_strlen(line)) == -1)
			//	{
			//		perror("Write failed");
			//		exit(EXIT_FAILURE);
			//	}
			//	printf("(%d) Sent %s\n", i, line);
			//}
			n = execve("/usr/bin/wc", cmd1, (void *)0);
			if (n == -1)
				perror("Execve failed");
			//read_result = read(pipes[i][0], buff, 100);
			//if (read_result == -1)
			//{
			//	perror("Read failed");
			//	exit(EXIT_FAILURE);
			//}
			//buff[read_result] = '\0';
			//printf("(%d) Got %s\n", i, buff);
			//x++;
			//if (write(pipes[i + 1][1], buff, ft_strlen(buff)) == -1)
			//{
			//	perror("Write failed");
			//	exit(EXIT_FAILURE);
			//}
			//printf("(%d) Sent %s\n", i, buff);
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			return (0);
		}
		i++;
	}
	j = 0;
	while (j < PROCESS_NUM + 1)
	{
		if (j != PROCESS_NUM)
			close(pipes[j][0]);
		if (j != 0)
			close(pipes[j][1]);
		j++;
	}
	//y = 5;

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
	printf("Main process sent %s\n", line);
	if (write(pipes[0][1], line, ft_strlen(line)) == -1)
	{
		perror("Write failed");
		exit(EXIT_FAILURE);
	}
	if (close(pipes[0][1]) == -1)
		perror("Close failed");
	//printf("Main process sent %d\n", y);
	//if (write(pipes[0][1], &y, sizeof(int)) == -1)
	//{
	//	perror("Write failed");
	//	exit(EXIT_FAILURE);
	//}
	line = malloc(100);
	if (read(pipes[PROCESS_NUM][0], line, 100) == -1)
	{
		perror("Main Read failed");
		exit(EXIT_FAILURE);
	}
	output_fd = open("outfile", O_WRONLY | O_CREAT, 0777);
	new_out_fd = dup2(output_fd, 1);
	write(1, line, ft_strlen(line));
	printf("Main recieved the final result. It is %s\n", line);
	close(output_fd);
	if (close(pipes[PROCESS_NUM][0]) == -1)
		perror("Close failed");
	i = 0;
	while (i < PROCESS_NUM)
	{
		wait(NULL);
		i++;
	}
	return(0);
}