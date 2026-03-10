/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:02:12 by huburton          #+#    #+#             */
/*   Updated: 2025/03/25 14:45:40 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_points(t_point *a, t_point *b)
{
	t_point	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	free_proj_points(t_point **points, int rows)
{
	int	i;

	if (!points)
		return ;
	i = 0;
	while (i < rows)
		free(points[i++]);
	free(points);
}
