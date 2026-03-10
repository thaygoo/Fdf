/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:59:58 by huburton          #+#    #+#             */
/*   Updated: 2025/03/26 13:13:28 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_bounds(t_bounds *bounds)
{
	bounds->min_x = INT_MAX;
	bounds->max_x = INT_MIN;
	bounds->min_y = INT_MAX;
	bounds->max_y = INT_MIN;
	bounds->min_z = INT_MAX;
	bounds->max_z = INT_MIN;
}

static void	update_bounds(t_bounds *b, t_point p)
{
	if (p.x < b->min_x)
		b->min_x = p.x;
	if (p.x > b->max_x)
		b->max_x = p.x;
	if (p.y < b->min_y)
		b->min_y = p.y;
	if (p.y > b->max_y)
		b->max_y = p.y;
}

static void	update_z_bounds(t_map *map, t_bounds *bounds)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
		{
			if (map->map[y][x] < bounds->min_z)
				bounds->min_z = map->map[y][x];
			if (map->map[y][x] > bounds->max_z)
				bounds->max_z = map->map[y][x];
		}
	}
}

void	get_bounds(t_map *map, t_bounds *bounds)
{
	int		x;
	int		y;
	t_point	p;
	t_point	proj;

	y = -1;
	init_bounds(bounds);
	while (++y < map->rows)
	{
		x = 0;
		x = -1;
		while (++x < map->cols)
		{
			p.x = x;
			p.y = y;
			p.z = map->map[y][x];
			proj = calc_iso_coords(p);
			update_bounds(bounds, proj);
		}
	}
	update_z_bounds(map, bounds);
}

int	get_scale(t_bounds *bounds)
{
	float	scale_x;
	float	scale_y;
	float	scale;

	scale_x = (RES_X * 0.85) / (bounds->max_x - bounds->min_x + 1);
	scale_y = (RES_Y * 0.85) / (bounds->max_y - bounds->min_y + 1);
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	if (scale < 1)
		return (1);
	if (scale > 50)
		return (50);
	return ((int)scale);
}
