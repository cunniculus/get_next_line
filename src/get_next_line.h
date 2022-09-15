#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# define TRUE 42
# define FALSE 0
typedef struct s_lst
{
	char			*line;
	struct s_lst 	*next;
}	t_lst;

typedef struct s_fddict
{
	int				fd;
	int				read;
	int				current_line;
	char			*buffer;
	t_lst			*lines;
	struct s_fddict	*next;
}	t_fddict;

char *get_next_line(int fd);
#endif
