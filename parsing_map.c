/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:00:00 by huburton          #+#    #+#             */
/*   Updated: 2025/03/25 14:28:31 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	allocate_map(t_map *map)
{
	int	i;

	if (map->rows <= 0 || map->cols <= 0)
		return (0);
	map->map = (int **)malloc(sizeof(int *) * map->rows);
	if (!map->map)
		return (0);
	i = 0;
	while (i < map->rows)
	{
		map->map[i] = (int *)malloc(sizeof(int) * map->cols);
		if (!map->map[i])
		{
			while (--i >= 0)
				free(map->map[i]);
			free(map->map);
			map->map = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

int	parse_number(const char **str)
{
	int	number;
	int	neg;

	while (**str == ' ' || **str == '\t')
		(*str)++;
	neg = 1;
	if (**str == '-')
	{
		neg = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	number = 0;
	while (**str >= '0' && **str <= '9')
	{
		number = number * 10 + (**str - '0');
		(*str)++;
	}
	while (**str && **str != ' ' && **str != '\t' && **str != '\n')
		(*str)++;
	return (number * neg);
}

static int	fill_map_row(const char *line, int *row, int cols)
{
	int	col;

	col = 0;
	while (*line && col < cols)
	{
		if (*line != ' ' && *line != '\t')
		{
			row[col++] = parse_number(&line);
		}
		else
			line++;
	}
	return (col == cols);
}

static int	process_buffer_line(t_buf_line *data)
{
	char	*line;

	if (data->i > data->line_start)
	{
		if (data->buffer[data->i] == '\n')
			data->buffer[data->i] = '\0';
		line = &data->buffer[data->line_start];
		if (!fill_map_row(line, data->map->map[*data->row], data->map->cols))
			return (0);
		(*data->row)++;
		if (data->buffer[data->i] == '\0')
			data->buffer[data->i] = '\n';
	}
	return (1);
}

int	fill_map_from_buffer(char *buffer, int size, t_map *map)
{
	int			i;
	int			line_start;
	int			row;
	t_buf_line	data;

	i = 0;
	line_start = 0;
	row = 0;
	while (i < size && row < map->rows)
	{
		if (buffer[i] == '\n' || i == size - 1)
		{
			data.buffer = buffer;
			data.i = i;
			data.line_start = line_start;
			data.map = map;
			data.row = &row;
			if (!process_buffer_line(&data))
				return (0);
			line_start = i + 1;
		}
		i++;
	}
	return (row == map->rows);
}
