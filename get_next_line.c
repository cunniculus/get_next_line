#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <bsd/string.h>

int line_feed(char *buff, int len);

char    *get_next_line(int fd)
{
    int     r;
    int     total;
    char    buff[BUFFER_SIZE];
    char    *line;
    int     found_line_feed;
    char    *tmp;

    found_line_feed = 0;

    total = 0;
    line = NULL;
    while ((r = read(fd, buff, BUFFER_SIZE)) && !found_line_feed)
    {
        if (line_feed(buff, r) >= 0)
        {
            r = line_feed(buff, r) + 1; 
            found_line_feed = 1;
        }
        if (total > 0)
        {
            tmp = strdup(line);
            free(line);
            line = calloc (1, total + r + 1);
            memmove(line, tmp, strlen(tmp));
            free(tmp);
        }
        else
            line = calloc (1, r + 1);
        memmove(&line[total], buff, r);
        total += r;
    }
    return (line);
}

int line_feed(char *buff, int len)
{
    int i;
    i = 0;
    while (i < len)
    {
        if (buff[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}
