/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:51:27 by huburton          #+#    #+#             */
/*   Updated: 2025/03/25 14:56:31 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_properly(t_map *map, t_mlx *mlx)
{
	free_map(map);
	clean_mlx(mlx);
	exit(0);
}

int	handle_key(int key, void *param)
{
	void	**params;

	params = (void **)param;
	if (key == XK_Escape)
	{
		exit_properly((t_map *)params[1], (t_mlx *)params[0]);
	}
	return (0);
}

int	handle_close(void *param)
{
	void	**params;

	params = (void **)param;
	exit_properly((t_map *)params[1], (t_mlx *)params[0]);
	return (0);
}
