/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:59:34 by huburton          #+#    #+#             */
/*   Updated: 2025/03/25 14:37:35 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->map)
		return ;
	i = -1;
	while (++i < map->rows)
		free(map->map[i]);
	free(map->map);
	map->map = NULL;
	map->rows = 0;
	map->cols = 0;
}

int	process_line(t_line_data *data)
{
	char	*line;
	int		col_count;

	if (data->i > data->line_start)
	{
		if (data->buffer[data->i] == '\n')
			data->buffer[data->i] = '\0';
		line = &data->buffer[data->line_start];
		col_count = count_tokens_fast(line);
		if (!*data->line_count)
			data->map->cols = col_count;
		else if (col_count != data->map->cols)
			return (0);
		(*data->line_count)++;
		if (data->buffer[data->i] == '\0')
			data->buffer[data->i] = '\n';
	}
	return (1);
}

static void	setup_parse_data(t_line_data *data, char *buffer, int i,
		t_parse_ctx *ctx)
{
	data->buffer = buffer;
	data->i = i;
	data->line_start = ctx->line_start;
	data->map = ctx->map;
	data->line_count = &ctx->line_count;
}

int	parse_buffer(char *buffer, int size, t_map *map)
{
	int			i;
	t_line_data	data;
	t_parse_ctx	ctx;

	i = 0;
	ctx.line_start = 0;
	ctx.line_count = 0;
	ctx.map = map;
	map->cols = 0;
	while (i < size)
	{
		if (buffer[i] == '\n' || i == size - 1)
		{
			setup_parse_data(&data, buffer, i, &ctx);
			if (!process_line(&data))
				return (0);
			ctx.line_start = i + 1;
		}
		i++;
	}
	map->rows = ctx.line_count;
	return (map->rows > 0 && map->cols > 0);
}

int	parsing(const char *filename, t_map *map)
{
	char	*buffer;
	int		size;

	buffer = read_file_chunked(filename, &size);
	if (!buffer)
		return (handle_buffer_error(NULL, "Can't read the file"));
	return (process_map_data(buffer, size, map));
}
