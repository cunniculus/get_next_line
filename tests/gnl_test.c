#include <unistd.h> //open() close ()
#include <stdlib.h> // free()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"


int main()
{
    int     fd;
    char    *line;

    fd = open("gnl_test.c", O_RDONLY);
    if (fd == -1)
    {
        printf("Fail to open()\n");
        return (1);
    }
	line = get_next_line(fd);
    printf("%s", line);
    if (close(fd) == -1)
    {
        printf("Fail to close()\n");
        return (1);
    }
    free(line);
    return (0);
}
