#include <fcntl.h>

int main()
{
	int infile_fd;

	infile_fd = open("infile",O_RDONLY);
	printf("%d\n", infile_fd);
	dup(infile_fd, 1);
	read(infile_fd, buff, 6);

}