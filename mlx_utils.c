/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:59:32 by huburton          #+#    #+#             */
/*   Updated: 2025/03/25 15:52:02 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clean_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->proj_points)
		free_proj_points(mlx->proj_points, mlx->proj_rows);
	if (mlx->img_ptr && mlx->mlx_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	if (mlx->win_ptr && mlx->mlx_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
}

void	setup_hooks(t_mlx *mlx, void *params)
{
	mlx_hook(mlx->win_ptr, KeyPress, KeyPressMask, handle_key, params);
	mlx_hook(mlx->win_ptr, DestroyNotify, NoEventMask, handle_close, params);
}
