/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:00:00 by huburton          #+#    #+#             */
/*   Updated: 2025/03/25 16:16:35 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_buffer_error(char *buffer, const char *msg)
{
	if (buffer)
		free(buffer);
	ft_printf("Error: %s\n", msg);
	return (0);
}

int	process_map_data(char *buffer, int size, t_map *map)
{
	if (!parse_buffer(buffer, size, map))
		return (handle_buffer_error(buffer, "Map dimension error"));
	if (!allocate_map(map))
		return (handle_buffer_error(buffer, "Malloc error"));
	if (!fill_map_from_buffer(buffer, size, map))
	{
		free_map(map);
		return (handle_buffer_error(buffer, "Reading map error"));
	}
	free(buffer);
	return (1);
}
