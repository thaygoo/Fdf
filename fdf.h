/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:00:15 by huburton          #+#    #+#             */
/*   Updated: 2025/03/25 15:52:02 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "resources/minilibx-linux/mlx.h"
# include "resources/libft/libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>

# define RES_X 1920
# define RES_Y 1600

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct s_bounds
{
	int	min_x;
	int	max_x;
	int	min_y;
	int	max_y;
	int	min_z;
	int	max_z;
}	t_bounds;

typedef struct s_map
{
	int	**map;
	int	rows;
	int	cols;
}	t_map;

typedef struct s_proj_data
{
	t_map		*map;
	t_point		***proj_points;
	t_bounds	*bounds;
	int			scale;
	int			x;
	int			y;
}	t_proj_data;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_data;
	int			bpp;
	int			size_line;
	int			endian;
	int			scale;
	int			proj_rows;
	t_bounds	bounds;
	t_point		**proj_points;
}	t_mlx;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	x;
	int	y;
	int	color;
}	t_line;

typedef struct s_line_data
{
	char	*buffer;
	int		i;
	int		line_start;
	t_map	*map;
	int		*line_count;
}	t_line_data;

typedef struct s_buf_line
{
	char	*buffer;
	int		i;
	int		line_start;
	t_map	*map;
	int		*row;
}	t_buf_line;

typedef struct s_buffer_info
{
	char	*buffer;
	int		line_start;
	t_map	*map;
	int		*line_count;
}	t_buffer_info;

typedef struct s_parse_ctx
{
	int		line_start;
	int		line_count;
	t_map	*map;
}	t_parse_ctx;

/* Fonctions de parsing */
int		parsing(const char *filename, t_map *map);
void	free_map(t_map *map);
char	*read_file_chunked(const char *filename, int *size);
int		count_tokens_fast(const char *line);
int		allocate_map(t_map *map);
int		fill_map_from_buffer(char *buffer, int size, t_map *map);
int		parse_number(const char **str);
int		parse_buffer(char *buffer, int size, t_map *map);
int		handle_buffer_error(char *buffer, const char *msg);
int		process_map_data(char *buffer, int size, t_map *map);
int		process_line(t_line_data *data);
void	init_parse_data(t_line_data *data, t_buffer_info *info);
int		process_buffer_char(int i, t_line_data *data, int *line_start);

/* Fonctions de projection */
void	scale_point(t_point *p, int scale);
void	get_bounds(t_map *map, t_bounds *bounds);
int		get_scale(t_bounds *bounds);
t_point	project_iso(t_point p, int scale);
t_point	center_point(t_point p, t_bounds bounds);
t_point	calc_iso_coords(t_point p);
int		compute_optimal_scale(t_map *map);
void	compute_proj_bounds(t_map *map, int scale, t_bounds *p_bounds);
void	precompute_projections(t_map *map, t_point ***proj_points,
			t_bounds *proj_bounds, int *opt_scale);
int		get_optimal_scale_result(int scale);

/* Fonctions de dessin */
void	draw_line(t_mlx *mlx, t_point start, t_point end);
void	put_pixel(t_mlx *mlx, int x, int y, int color);
void	draw_map(t_mlx *mlx, t_map *map);
void	draw_point_connections(t_mlx *mlx, t_map *map, int x, int y);

/* Fonctions MLX et utilitaires */
void	exit_properly(t_map *map, t_mlx *mlx);
int		handle_key(int key, void *param);
int		handle_close(void *param);
void	setup_hooks(t_mlx *mlx, void *params);
void	clean_mlx(t_mlx *mlx);
int		check_args(int ac, char *av[]);
int		init_mlx_window(t_mlx *mlx, t_map *map);
void	free_proj_points(t_point **points, int rows);
void	ft_swap(int *a, int *b);
void	ft_swap_points(t_point *a, t_point *b);

/* Fonctions d'initialisation */
int		init_structures(t_map *map, t_mlx *mlx);
int		setup_map_and_mlx(t_map *map, t_mlx *mlx, char *file);

#endif
