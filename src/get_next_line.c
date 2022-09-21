/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:50:48 by guolivei          #+#    #+#             */
/*   Updated: 2022/09/21 22:57:27 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		nl_in_temp(char *temp);
char	*ft_strjoin(char **s1, char *s2);
int		ft_strlen(char *str);
char	*update_temp(char **temp, char *line);
char	*get_line(char *str, int current_read);

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1]; // buffer to read into
	static char *temp; // var to store chars read in between calls
	char		*line;
	int			current_read; // number of chars read from read() function

	// while temp has no '\n' char
		// read BUFFER_SIZE bytes
		// append it to temp
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
	line = get_line(temp, current_read);
	temp = update_temp(&temp, line);
	return (line);
}

int	nl_in_temp(char *temp)
{
	// in case temp is NULL
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

char	*ft_strjoin(char **s1, char *s2)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(*s1) + ft_strlen(s2);;
	str = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (*s1 && (*s1)[i])
	{
		str[i] = (*s1)[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[len] = '\0';
	if (*s1)
		free(*s1);
	return (str);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*get_line(char *str, int current_read)
{
	int		len;
	int		i;
	char	*line;

	current_read = 0;

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
