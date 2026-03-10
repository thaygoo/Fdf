/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:59:27 by huburton          #+#    #+#             */
/*   Updated: 2025/03/26 12:54:38 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_args(int ac, char *av[])
{
	if (ac != 2)
	{
		ft_printf("Error: use ./fdf <map.fdf>\n");
		return (0);
	}
	if (access(av[1], F_OK) == -1)
	{
		ft_printf("Error: Unknow file\n");
		return (0);
	}
	return (1);
}

static void	render_and_loop(t_mlx *mlx, t_map *map)
{
	void	*params[2];

	precompute_projections(map, &mlx->proj_points, &mlx->bounds, &mlx->scale);
	draw_map(mlx, map);
	params[0] = mlx;
	params[1] = map;
	setup_hooks(mlx, params);
	mlx_loop(mlx->mlx_ptr);
}

int	main(int ac, char *av[])
{
	t_map	map;
	t_mlx	mlx;

	if (!check_args(ac, av))
		return (1);
	init_structures(&map, &mlx);
	if (!setup_map_and_mlx(&map, &mlx, av[1]))
		return (1);
	render_and_loop(&mlx, &map);
	return (0);
}
