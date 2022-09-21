#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# define TRUE 42
# define FALSE 0
# define MAIN_LIST 1
# define SEC_LIST 2

typedef struct s_fddict
{
	int				fd;
	int				lines_stored;
	char			**lines;
	struct s_fddict	*next;
}	t_fddict;

char *get_next_line(int fd);
#endif
