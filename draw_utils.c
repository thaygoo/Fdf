/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:59:50 by huburton          #+#    #+#             */
/*   Updated: 2025/03/20 17:01:38 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_point_connections(t_mlx *mlx, t_map *map, int x, int y)
{
	t_point	p0;

	p0 = mlx->proj_points[y][x];
	if (x < map->cols - 1)
		draw_line(mlx, p0, mlx->proj_points[y][x + 1]);
	if (y < map->rows - 1)
		draw_line(mlx, p0, mlx->proj_points[y + 1][x]);
}

static void	compute_single_point(t_proj_data data)
{
	t_point	raw;
	t_point	proj;

	raw.x = data.x;
	raw.y = data.y;
	raw.z = data.map->map[data.y][data.x];
	proj = project_iso(raw, data.scale);
	(*data.proj_points)[data.y][data.x] = center_point(proj, *data.bounds);
}

static void	compute_points(t_map *map, t_point ***proj_points,
		t_bounds *bounds, int scale)
{
	int			y;
	int			x;
	t_proj_data	data;

	data.map = map;
	data.proj_points = proj_points;
	data.bounds = bounds;
	data.scale = scale;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			data.x = x;
			data.y = y;
			compute_single_point(data);
			x++;
		}
		y++;
	}
}

static int	allocate_proj_points(t_map *map, t_point ***proj_points)
{
	int	y;

	*proj_points = malloc(sizeof(t_point *) * map->rows);
	if (!(*proj_points))
		return (0);
	y = 0;
	while (y < map->rows)
	{
		(*proj_points)[y] = malloc(sizeof(t_point) * map->cols);
		if (!(*proj_points)[y])
		{
			free_proj_points(*proj_points, y);
			return (0);
		}
		y++;
	}
	return (1);
}

void	precompute_projections(t_map *map, t_point ***proj_points,
		t_bounds *proj_bounds, int *opt_scale)
{
	*opt_scale = compute_optimal_scale(map);
	compute_proj_bounds(map, *opt_scale, proj_bounds);
	if (!allocate_proj_points(map, proj_points))
		return ;
	compute_points(map, proj_points, proj_bounds, *opt_scale);
}
