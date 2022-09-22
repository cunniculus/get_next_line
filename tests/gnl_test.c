#include <unistd.h> //open() close ()
#include <stdlib.h> // free()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main()
{
    int     fd[5];
    char    *line;
	
	int r = read(42, 0, 5);
	printf("read(42, 0, 5): output = %d\n", r);
	r = read(42, 0, 0);
	printf("read(42, 0, 0): output = %d\n", r);
	r = read(0, 0, 1);
	printf("read(0, 0, 0): output = %d\n", r);

// --- a_nl.txt // 
    fd[0] = open("test_files/a_nl.txt", O_RDONLY);
	r = read(fd[0], 0, 0);
	printf("read(%d, 0, 0): output = %d\n", fd[0], r);
    if (fd[0] == -1)
    {
        printf("Fail to open()\n");
        return (1);
    }
	printf("já vai entrar na get_next_line.\n");
	printf("the value of BUFFER_SIZE is: %d\n", BUFFER_SIZE);
	line = get_next_line(fd[0]);
    printf("line 1: %s", line);
    free(line);

	line = get_next_line(fd[0]);
    printf("there is no second line: %s", line);
	if (!line)
		printf("get_next_line return NULL\n");
	else 
		free(line);

    if (close(fd[0]) == -1)
    {
        printf("Fail to close()\n");
        return (1);
    }

	printf("\nempty file\n");
// --- empty.txt // 
    fd[0] = open("test_files/empty_file.txt", O_RDONLY);
    if (fd[0] == -1)
    {
        printf("Fail to open()\n");
        return (1);
    }
	line = get_next_line(fd[0]);
    printf("there is nothing to be read: %s\n", line);
	if (!line)
		printf("empty file --> get_next_line return NULL\n");
	else 
		free(line);
    if (close(fd[0]) == -1)
    {
        printf("Fail to close()\n");
        return (1);
    }

// a-k.txt
    fd[1] = open("test_files/a-k.txt", O_RDONLY);
    if (fd[1] == -1)
    {
        printf("Fail to open()\n");
        return (1);
    }
	int i = 1;
	while ((line = get_next_line(fd[1])))
	{
    	printf("line %d: %s", i, line);
		if (!line)
			printf("empty file --> get_next_line return NULL\n");
		else 
			free(line);
		i++;
	}

    if (close(fd[1]) == -1)
    {
        printf("Fail to close()\n");
        return (1);
    }
    return (0);
}
