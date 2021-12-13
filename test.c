#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	char	*buff;
	int infile_fd;
	int output_fd;

	buff = (char *)malloc(21 + 1);
	infile_fd = open("infile",O_RDONLY);
	output_fd = open("outfile", O_WRONLY);
	printf("%d\n", infile_fd);
	dup2(output_fd, 0);
	read(infile_fd, buff, 201);
	buff[21] = '\0';
	//write(1, buff, strlen(buff));
}