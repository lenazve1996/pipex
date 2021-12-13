#include "libft.h"
#include <stdio.h>
# define PROCESS_NUM 3

int	main(int argc, char **argv)
{
	int	pipes[PROCESS_NUM+1][2];
	int	i;
	int j;
	int x;
	int y;
	int pids[PROCESS_NUM];

	if (argc < 5)
	{
		ft_putstr_fd("The number of arguments should be at least 4\n", 2);
		return (0);
	}

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
					close (pipes[j][0]);
				if (i + 1 != j)
					close (pipes[j][1]);
				j++;
			}
			if (read(pipes[i][0], &x, sizeof(int)) == -1)
			{
				perror("Read failed");
				exit(EXIT_FAILURE);
			}
			printf("(%d) Got %d\n", i, x);
			x++;
			if (write(pipes[i+1][1], &x, sizeof(int)) == -1)
			{
				perror("Write failed");
				exit(EXIT_FAILURE);
			}
			printf("(%d) Sent %d\n", i, x);
			close(pipes[i][0]);
			close(pipes[i+1][1]);
			return (0);
		}
		i++;
	}
	y = 5;
	printf("Main process sent %d\n", y);
	if (write(pipes[0][1], &y, sizeof(int)) == -1)
	{
		perror("Write failed");
		exit(EXIT_FAILURE);
	}
	if (read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1)
	{
		perror("Read failed");
		exit(EXIT_FAILURE);
	}
	printf("Main recieved the final result. It is %d\n", y);
	i = 0;
	while (i < PROCESS_NUM)
	{
		wait(NULL);
		i++;
	}
}