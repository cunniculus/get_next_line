/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:02:25 by guolivei          #+#    #+#             */
/*   Updated: 2022/09/16 00:10:17 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> // REMOVER

static			t_fddict	*ft_lstnew(int	fd);
static void		ft_lstadd_back(t_fddict **lst, t_fddict *new);
static int		is_new_fd(const t_fddict *lst, int fd);
static int		set_buffer(char **buffer, int fd);
//static void		ft_lstdelone(t_fddict *lst, void (*del)(void*));
//static void		ft_lstclear(t_fddict **lst, void (*del)(void *));
static size_t	count_nl(char *s);
static int		split(t_fddict **lst, char *buffer);

char *get_next_line(int fd)
{
	static t_fddict	*fd_lst;
	t_fddict *tmp;
	char *buffer;
	int	read;

	// checks if fd is beeing read for the first time
	// if so, node is created for this fd
	if (is_new_fd(fd_lst, fd))
	{
		printf("fd is %d\n", fd);
		ft_lstadd_back(&fd_lst, ft_lstnew(fd));
		printf("new node created with fd %d\n", fd);
		if (!fd_lst)
			return (NULL);
	}
	tmp = fd_lst;
	while(tmp->fd != fd)
		tmp = tmp->next;
	printf("tmp\n");
	// if no line was read this fd before
	// read as much as BUFFER_SIZE bytes
	read = -1;
	if (fd_lst->lines_stored == 0)
	{
		printf("no lines_stored\n");
		read = set_buffer(&buffer, fd);
		while (read && split(&tmp, buffer))
			;
		printf("saiu do while\n");

	}
	if (!read)
		return (NULL);
	printf("buffer: %s\n", buffer);
	return (buffer);
}

static t_fddict	*ft_lstnew(int	fd)
{
	t_fddict *node;
	printf("inside lstnew\n");
	node = NULL;
	node = (t_fddict *) malloc(sizeof (t_fddict));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->next = NULL;
	return (node);
}

static void	ft_lstadd_back(t_fddict **lst, t_fddict *new)
{
	t_fddict	*tmp;

	printf("inside lstadd_back\n");
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			tmp->next = new;
			return ;
		}
		tmp = tmp->next;
	}
}

static int	is_new_fd(const t_fddict *lst, int fd)
{
	while (lst)
	{
		if (lst->fd == fd)
			return (FALSE);
		lst = lst->next;
	}
	return (TRUE); 
}

static int	set_buffer(char **buffer, int fd)
{
	int	r;

	printf("inside set_buffer\n");
	*buffer = malloc (BUFFER_SIZE + 1);
	r = read(fd, *buffer, BUFFER_SIZE);
	if (!r)
		return (0);
	(*buffer)[r] = '\0';
	printf("end of set_buffer\n");
	return (r);

}
/*
static void	ft_lstclear(t_fddict **lst, void (*del)(void *))
{
	t_fddict	*tmp;
	int			i;

	i = 0;
	while (*lst)
	{
		tmp = (*lst)->next;
		while (((*lst)->lines)[i])
		{
			del(((*lst)->lines)[i]);
			i++;
		}
		del((*lst)->lines);
		free(*lst);
		*lst = tmp;
	}
}
*/
/*
static void	ft_lstdelone(t_fddict *lst, void (*del)(void*))
{
	int	i;

	i = 0;
	while ((lst->lines)[i])
	{
		del((lst->lines)[i]);
		i++;
	}
	del(lst->lines);
	free(lst);
}
*/

static size_t	count_nl(char *s)
{
	size_t	nl;

	nl = 0;
	while (*s)
	{
		if (*s == '\n')
			nl++;
		s++;
	}
	return (nl);
}

// splits buffer into stirngs separated by '\n'
// return 0 if no '\n' was found in buffer, number > 0 otherwise
static int split(t_fddict **lst, char *buffer)
{
	int lines;
	int	s_index;
	int	c_index;

	(*lst)->lines_stored = count_nl(buffer) + 1;
	(*lst)->lines = malloc (sizeof (char *) * ((*lst)->lines_stored + 1));
	s_index = 0;
	lines = 0;
	while (lines < (*lst)->lines_stored)
	{
		((*lst)->lines)[s_index] = malloc (BUFFER_SIZE + 1);
		c_index = 0;
		while (*buffer && *buffer != '\n')
		{
			((*lst)->lines)[s_index][c_index] = *buffer;
			buffer++;
			c_index++;
		}
		((*lst)->lines)[s_index][c_index] = '\0';
		s_index++;
		lines++;
	}
	((*lst)->lines)[s_index] = NULL;
	return ((*lst)->lines_stored == 1);
}
