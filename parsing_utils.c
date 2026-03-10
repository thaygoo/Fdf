/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:00:00 by huburton          #+#    #+#             */
/*   Updated: 2025/03/25 14:17:08 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define CHUNK_SIZE 8192

int	count_tokens_fast(const char *line)
{
	int	count;
	int	in_num;

	count = 0;
	in_num = 0;
	while (*line)
	{
		if (*line == ' ' || *line == '\t' || *line == '\n')
			in_num = 0;
		else if (!in_num)
		{
			in_num = 1;
			count++;
		}
		line++;
	}
	return (count);
}

static int	allocate_new_buffer(char **buffer, char **new_buffer,
		int total_size, int new_capacity)
{
	*new_buffer = (char *)malloc(new_capacity);
	if (!*new_buffer)
	{
		if (*buffer)
			free(*buffer);
		return (0);
	}
	if (*buffer)
	{
		ft_memcpy(*new_buffer, *buffer, total_size);
		free(*buffer);
	}
	*buffer = *new_buffer;
	return (1);
}

static int	read_chunk(int fd, char **buffer, int *total_size, int *capacity)
{
	char	chunk[CHUNK_SIZE];
	char	*new_buffer;
	int		bytes_read;

	bytes_read = read(fd, chunk, CHUNK_SIZE);
	if (bytes_read <= 0)
		return (bytes_read);
	if (*total_size + bytes_read + 1 > *capacity)
	{
		*capacity = *total_size + bytes_read + CHUNK_SIZE;
		if (!allocate_new_buffer(buffer, &new_buffer, *total_size, *capacity))
			return (-1);
	}
	ft_memcpy(*buffer + *total_size, chunk, bytes_read);
	*total_size += bytes_read;
	return (bytes_read);
}

static int	process_file_content(int fd, char **buffer, int *size)
{
	int	total_size;
	int	capacity;
	int	read_result;

	*buffer = NULL;
	total_size = 0;
	capacity = 0;
	while (1)
	{
		read_result = read_chunk(fd, buffer, &total_size, &capacity);
		if (read_result < 0)
		{
			if (*buffer)
				free(*buffer);
			*buffer = NULL;
			return (0);
		}
		if (read_result == 0)
			break ;
	}
	*size = total_size;
	return (1);
}

char	*read_file_chunked(const char *filename, int *size)
{
	int		fd;
	char	*buffer;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!process_file_content(fd, &buffer, size))
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	if (buffer)
		buffer[*size] = '\0';
	return (buffer);
}
