/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:30:00 by huburton          #+#    #+#             */
/*   Updated: 2025/03/25 16:19:20 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_mlx_window(t_mlx *mlx, t_map *map)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
	{
		free_map(map);
		return (0);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, RES_X, RES_Y, "FDF");
	if (!mlx->win_ptr)
	{
		clean_mlx(mlx);
		free_map(map);
		return (0);
	}
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, RES_X, RES_Y);
	if (!mlx->img_ptr)
	{
		clean_mlx(mlx);
		free_map(map);
		return (0);
	}
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp,
			&mlx->size_line, &mlx->endian);
	return (1);
}

int	init_structures(t_map *map, t_mlx *mlx)
{
	ft_memset(map, 0, sizeof(t_map));
	ft_memset(mlx, 0, sizeof(t_mlx));
	return (1);
}

int	setup_map_and_mlx(t_map *map, t_mlx *mlx, char *file)
{
	if (!parsing(file, map))
	{
		return (0);
	}
	get_bounds(map, &mlx->bounds);
	mlx->scale = get_scale(&mlx->bounds);
	mlx->proj_rows = map->rows;
	if (!init_mlx_window(mlx, map))
		return (0);
	return (1);
}
