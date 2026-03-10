/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:05:39 by huburton          #+#    #+#             */
/*   Updated: 2025/03/20 17:05:56 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	calc_iso_coords(t_point p)
{
	double	angle;
	double	cos30;
	double	sin30;
	t_point	iso;

	angle = 0.523599;
	cos30 = cos(angle);
	sin30 = sin(angle);
	iso.x = (int)((p.x - p.y) * cos30);
	iso.y = (int)(-p.z + (p.x + p.y) * sin30);
	iso.z = p.z;
	return (iso);
}

t_point	project_iso(t_point p, int scale)
{
	t_point	iso;

	scale_point(&p, scale);
	iso = calc_iso_coords(p);
	return (iso);
}
