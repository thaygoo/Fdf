/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:00:01 by huburton          #+#    #+#             */
/*   Updated: 2025/03/20 17:07:01 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_point(t_point *p, int scale)
{
	p->x *= scale;
	p->y *= scale;
	p->z *= scale;
}

static void	update_bounds(t_bounds *p_bounds, t_point p, int x, int y)
{
	if (x == 0 && y == 0)
	{
		p_bounds->min_x = p.x;
		p_bounds->max_x = p.x;
		p_bounds->min_y = p.y;
		p_bounds->max_y = p.y;
	}
	else
	{
		if (p.x < p_bounds->min_x)
			p_bounds->min_x = p.x;
		if (p.x > p_bounds->max_x)
			p_bounds->max_x = p.x;
		if (p.y < p_bounds->min_y)
			p_bounds->min_y = p.y;
		if (p.y > p_bounds->max_y)
			p_bounds->max_y = p.y;
	}
}

void	compute_proj_bounds(t_map *map, int scale, t_bounds *p_bounds)
{
	int		x;
	int		y;
	t_point	p;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			p = project_iso((t_point){x, y, map->map[y][x]}, scale);
			update_bounds(p_bounds, p, x, y);
			x++;
		}
		y++;
	}
}

int	compute_optimal_scale(t_map *map)
{
	int			scale;
	t_bounds	b;

	scale = 1;
	while (1)
	{
		compute_proj_bounds(map, scale, &b);
		if ((b.max_x - b.min_x) > (int)(RES_X * 0.9) ||
			(b.max_y - b.min_y) > (int)(RES_Y * 0.9))
			break ;
		scale++;
	}
	if (scale - 1 > 0)
		return (scale - 1);
	return (1);
}

t_point	center_point(t_point p, t_bounds bounds)
{
	int	offset_x;
	int	offset_y;

	offset_x = (RES_X - (bounds.max_x - bounds.min_x)) / 2 - bounds.min_x;
	offset_y = (RES_Y - (bounds.max_y - bounds.min_y)) / 2 - bounds.min_y;
	p.x += offset_x;
	p.y += offset_y;
	return (p);
}
