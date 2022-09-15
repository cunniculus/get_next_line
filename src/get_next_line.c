/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:02:25 by guolivei          #+#    #+#             */
/*   Updated: 2022/09/15 19:55:33 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> // REMOVER

static t_fddict	*ft_lstnew(int	fd);
static void	ft_lstadd_back(t_fddict **lst, t_fddict *new);
static int	is_new_fd(const t_fddict *lst, int fd);
static int	set_buffer(char **buffer, int fd);

char *get_next_line(int fd)
{
	static t_fddict	*fd_lst;
	char *buffer;
	int	read;

	buffer = 0;
	if (!fd_lst || is_new_fd(fd_lst, fd))
	{
		printf("new node created with fd %d\n", fd);
		ft_lstadd_back(&fd_lst, ft_lstnew(fd));
		if (!fd_lst)
			return (NULL);
	}
	read = set_buffer(&buffer, fd);
	printf("buffer: %s\n", buffer);

	return (buffer);
}

static t_fddict	*ft_lstnew(int	fd)
{
	t_fddict *node;

	node = NULL;
	node = (t_fddict *) malloc(sizeof (t_fddict));
	if (node == NULL)
		return (NULL);
	node->fd = fd;
	node->next = NULL;
	return (node);
}

static void	ft_lstadd_back(t_fddict **lst, t_fddict *new)
{
	t_fddict	*tmp;

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

	*buffer = malloc (BUFFER_SIZE + 1);
	r = read(fd, *buffer, BUFFER_SIZE);
	*buffer[r] = '\0';
	return (r);

}
