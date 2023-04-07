/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:52:03 by mliew             #+#    #+#             */
/*   Updated: 2022/12/29 16:49:15 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// joins str1 with str2 in temp and then frees str1 to prevent leaks
char	*join_free(char *str1, char *str2)
{
	char	*temp;

	temp = ft_strjoin(str1, str2);
	free(str1);
	return (temp);
}

// gets rest of buffer after /n if there are extra
char	*continue_next(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

// takes out line before \n or \0
char	*take_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

// loop to read everything in file and store as a new buffer
char	*read_file(int fd, char *new)
{
	char	*buffer;
	int		byte_read;

	if (!new)
		new = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		buffer[byte_read] = 0;
		new = join_free(new, buffer);
		if (ft_strchr(new, '\n'))
			break ;
	}
	free(buffer);
	return (new);
}

// get_next_line reads BUFFER_SIZE until buffer contains a '\n'
// then it takes the string until '\n' and returns it
// it also takes the rest of the string after '\n' in buffer and overwrites 
// itself so that the next time it continues there as it is a static variable
// in bonus buffer is a 2d array so it can open multiple fd
char	*get_next_line(int fd)
{
	static char	*buf[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf[fd] = read_file(fd, buf[fd]);
	if (!buf[fd])
		return (NULL);
	line = take_line(buf[fd]);
	buf[fd] = continue_next(buf[fd]);
	return (line);
}

// int	main(void)
// {
	// int	fd1 = open("text.txt", O_RDONLY);
	// int	fd2 = open("text2.txt", O_RDONLY);
	// int	fd3 = open("text3.txt", O_RDONLY);
	// printf("%s", get_next_line(fd1));
	// printf("%s", get_next_line(fd2));
	// printf("%s", get_next_line(fd3));
	// printf("%s", get_next_line(fd1));
	// printf("%s", get_next_line(fd2));
	// printf("%s", get_next_line(fd3));
	// printf("%s", get_next_line(fd1));
	// printf("%s", get_next_line(fd2));
	// printf("%s", get_next_line(fd3));
	// printf("%s", get_next_line(fd1));
	// printf("%s", get_next_line(fd2));
	// printf("%s", get_next_line(fd3));
// }
