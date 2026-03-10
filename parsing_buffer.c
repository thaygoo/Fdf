/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:35:00 by huburton          #+#    #+#             */
/*   Updated: 2025/03/25 14:32:55 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_parse_data(t_line_data *data, t_buffer_info *info)
{
	data->buffer = info->buffer;
	data->line_start = info->line_start;
	data->map = info->map;
	data->line_count = info->line_count;
}

int	process_buffer_char(int i, t_line_data *data, int *line_start)
{
	data->i = i;
	if (!process_line(data))
		return (0);
	*line_start = i + 1;
	return (1);
}
