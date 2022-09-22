/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:50:48 by guolivei          #+#    #+#             */
/*   Updated: 2022/09/22 00:06:10 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		nl_in_temp(char *temp);
char	*ft_strjoin(char **s1, char *s2);
int		ft_strlen(char *str);
char	*update_temp(char **temp, char *line);
char	*get_line(char *str);

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*temp;
	char		*line;
	int			current_read;

	while (!nl_in_temp(temp))
	{
		current_read = read(fd, buffer, BUFFER_SIZE);
		if (!current_read)
			break ;
		buffer[current_read] = '\0';
		printf("Current_read: %d\n", current_read);
		printf("buffer = %s\n", buffer);
		temp = ft_strjoin(&temp, buffer);
		printf("temp = %s\n", temp);
	}
	line = get_line(temp);
	temp = update_temp(&temp, line);
	return (line);
}

int	nl_in_temp(char *temp)
{
	if (!temp)
		return (FALSE);
	while (*temp)
	{
		if ('\n' == *temp)
			return (TRUE);
		temp++;
	}
	return (FALSE);
}

char	*get_line(char *str)
{
	int		len;
	int		i;
	char	*line;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != '\n' && str[len])
		len++;
	if (str[len] == '\n')
		len++;
	line = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		line[i] = str[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

char	*update_temp(char **temp, char *line)
{
	int	len;
	int cut;
	int i;
	char *new_temp;

    if (!(*temp))
		return (0);
	len = ft_strlen(*temp);
	cut = ft_strlen(line);
	if (len == cut)
	{
		free(*temp);
		return (NULL);
	}
	new_temp = malloc(sizeof(char) * (len + 1 - cut));
	i = 0;
	while ((*temp)[cut])
	{
		new_temp[i] = (*temp)[cut];
		cut++;
		i++;
	}
	new_temp[i] = '\0';
	free (*temp);
	return (new_temp);
}
