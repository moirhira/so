/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:57:04 by moirhira          #+#    #+#             */
/*   Updated: 2024/11/13 22:04:02 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Custom implementation of strdup
char	*my_strdup(char *src)
{
	char	*dup;
	int		len;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	len = calclen(src);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

// str convatination
void	ft_strcat(char *dest, const char *src)
{
	int	dest_len;
	int	i;

	dest_len = calclen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
}

// helper function in read from fd uppend data to buffer
char	*append_to_buffer(char *buffer, char *buf, int readed)
{
	char	*temp;

	if (!buffer)
		buffer = my_strdup(buf);
	else
	{
		temp = buffer;
		buffer = malloc(calclen(temp) + readed + 1);
		if (!buffer)
		{
			free(temp);
			return (NULL);
		}
		ft_copy(buffer, temp);
		ft_strcat(buffer, buf);
		free(temp);
	}
	return (buffer);
}

// read from fd and add data to buffer until \n or end of file 
char	*readfromfd(int fd, char *buffer)
{
	char	*buf;
	int		readed;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	readed = read(fd, buf, BUFFER_SIZE);
	while (readed > 0)
	{
		if (readed == -1)
		{
			free(buf);
			free(buffer);
			return (NULL);
		}
		buf[readed] = '\0';
		buffer = append_to_buffer(buffer, buf, readed);
		if (find_newline(buffer, '\n'))
			break ;
		readed = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (buffer);
}

//main function
char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*line;

	if (!find_newline(buffer, '\n'))
	{
		buffer = readfromfd(fd, buffer);
		if (!buffer)
			return (NULL);
	}
	line = separate_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
// 	int fd = open("tt.txt", O_RDWR);
// 	char *s = get_next_line(fd);
// 	printf("%s", s);
// 	free(s);
// 	s = get_next_line(fd);
// 	while (s)
// 	{
// 		free(s);
// 		s = get_next_line(fd);
// 	}
// 	free(s);
// 	close(fd);
// 	return (0);
// }