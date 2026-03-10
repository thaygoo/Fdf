/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:59:47 by huburton          #+#    #+#             */
/*   Updated: 2025/03/20 14:09:33 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int	pos;

	if (x < 0 || x >= RES_X || y < 0 || y >= RES_Y)
		return ;
	pos = (y * mlx->size_line) + (x * (mlx->bpp / 8));
	if (pos >= 0 && pos < RES_X * RES_Y * (mlx->bpp / 8))
		*(int *)(mlx->img_data + pos) = color;
}

static void	init_line_values(t_line *l, t_point start, t_point end)
{
	l->dx = end.x - start.x;
	l->dy = abs(end.y - start.y);
	l->err = l->dx / 2;
	l->sx = 1;
	if (start.y < end.y)
		l->sy = 1;
	else
		l->sy = -1;
	l->x = start.x;
	l->y = start.y;
	l->color = 0xFFFFFF;
}

static void	handle_steep_case(t_point *start, t_point *end, int *steep)
{
	if (abs(end->y - start->y) > abs(end->x - start->x))
	{
		ft_swap(&start->x, &start->y);
		ft_swap(&end->x, &end->y);
		*steep = 1;
	}
	else
		*steep = 0;
	if (start->x > end->x)
		ft_swap_points(start, end);
}

void	draw_line(t_mlx *mlx, t_point start, t_point end)
{
	t_line	l;
	int		steep;

	if ((start.x < 0 && end.x < 0) || (start.x >= RES_X && end.x >= RES_X)
		|| (start.y < 0 && end.y < 0) || (start.y >= RES_Y && end.y >= RES_Y))
		return ;
	handle_steep_case(&start, &end, &steep);
	init_line_values(&l, start, end);
	while (l.x <= end.x)
	{
		if (steep)
			put_pixel(mlx, l.y, l.x, l.color);
		else
			put_pixel(mlx, l.x, l.y, l.color);
		l.err -= l.dy;
		if (l.err < 0)
		{
			l.y += l.sy;
			l.err += l.dx;
		}
		l.x += l.sx;
	}
}

void	draw_map(t_mlx *mlx, t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			draw_point_connections(mlx, map, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}
