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

// --- a_nl.txt // 
    fd[0] = open("test_files/a_nl.txt", O_RDONLY);
    if (fd[0] == -1)
    {
        printf("Fail to open()\n");
        return (1);
    }
	line = get_next_line(fd[0]);
    printf("%s", line);
    free(line);

	line = get_next_line(fd[0]);
    printf("%s", line);
    free(line);

// a_nl10x.txt
    fd[1] = open("test_files/a_nl10x.txt", O_RDONLY);
    if (fd[1] == -1)
    {
        printf("Fail to open()\n");
        return (1);
    }
	line = get_next_line(fd[1]);
    printf("%s", line);
    free(line);

    if (close(fd[0]) == -1)
    {
        printf("Fail to close()\n");
        return (1);
    }
    if (close(fd[1]) == -1)
    {
        printf("Fail to close()\n");
        return (1);
    }
    return (0);
}
