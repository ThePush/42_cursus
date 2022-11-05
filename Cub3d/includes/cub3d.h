/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:02:39 by jsemel            #+#    #+#             */
/*   Updated: 2022/06/10 11:38:48 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** External libraries
*/

# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdint.h>

/*
** Static libraries
*/
# include "libft.h"
# include <mlx.h>

/*
** ANSI color codes
*/
# define KNRM "\x1B[0m"
# define KRED "\x1B[31m"
# define KGRN "\x1B[32m"

/*
** Constants
*/

# define VALID_CHARS "01NSEW "
# define SCALE 256
# define VIEW_ANGLE 60
# define MAX_LINE 20000

/*
** Keycodes
*/

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define L_ARROW 65361
# define R_ARROW 65363

/*
** X11 Events and masks
*/

# define CROSS_DESTROY 33
# define KEY_PRESS 02
# define KEY_RELEASE 03
# define M_DESTROY 0
# define M_KEY_PRESS 1
# define M_KEY_RELEASE 2

/*
** Max resolutions
*/

# define RES_WIDTH 1920
# define RES_HEIGHT 1080

/*
** Structures
*/

typedef struct s_img
{
	void		*img_ptr;
	int			*data;
	int			bpp;
	int			size_l;
	int			endian;
}				t_img;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_img		img;
}				t_mlx;

typedef struct s_res
{
	long long	width;
	long long	height;
}				t_res;

typedef struct s_texture
{
	char		*path;
	int			width;
	int			height;
	t_img		img;
}				t_texture;

typedef struct s_color
{
	int			argb;
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_map
{
	char		**matrix;
	int			width;
	int			height;
}				t_map;

typedef struct s_data
{
	t_color		floor;
	t_color		ceilling;
	t_texture	no_xpm;
	t_texture	so_xpm;
	t_texture	we_xpm;
	t_texture	ea_xpm;
	t_res		res;
	t_map		map;
}				t_data;

typedef struct s_player
{
	double		x;
	double		y;
	double		radius;
	double		move_speed;
	double		rotation_angle;
	double		rotation_speed;
	char		move_direction;
	int			turn_direction;
}				t_player;

typedef struct s_ray
{
	double		x;
	double		y;
	double		size;
	double		angle;
	double		x_step;
	double		y_step;
	char		w_block;
	char		orientation;
	char		side;
}				t_ray;

typedef struct s_rays
{
	t_ray		*arr;
	double		fov;
	double		proj_plane_dist;
}				t_rays;

typedef struct s_game
{
	t_mlx		mlx;
	t_data		datas;
	t_player	player;
	t_rays		rays;
}				t_game;

/*
** Graphical
*/

typedef struct s_rect
{
	int			x;
	int			y;
	int			fill_color;
	int			border_color;
	int			border_width;
	double		width;
	double		height;
	t_texture	tex;
}				t_rect;

typedef struct s_line
{
	int			begin_x;
	int			begin_y;
	int			end_x;
	int			end_y;
	int			color;
	int			width;
}				t_line;

/*
** cub3d
*/

void			load_data(int fd, t_data *datas);
void			check_data(t_data *datas);
void			display_window(t_game *game);

/*
** check_scene1
*/

void			check_resolution(t_res *res);

/*
** check_scene2
*/

void			check_map(t_data *datas);
void			check_map2(t_data *datas);

/*
** cast ray
*/
void			matrix_x_crossing(t_ray *ray, t_map *map, t_player *player);
void			matrix_y_crossing(t_ray *ray, t_map *map, t_player *player);

/*
** draw_walls2
*/

void			display_wall_ray(t_rect *rect, int *img, t_res *res,
					t_ray *ray);
int				get_bitmap_offset(t_ray *ray, int bitmap_width);

/*
** draw
*/
void			display_walls(t_game *game);

/*
** get_scene2
*/
void			parse_map(int fd, char *line, t_map *map);

/*
** ready game
*/

void			init_player(t_game *game);
void			init_hooks(t_game *game);
void			init_xpm(t_game *game);
void			init_rays(t_game *game);

/*
** render game
*/

void			init_all(t_game *game);
void			update(t_game *game);
void			display_game(t_game *game);
int				routine(void *my_struct);

/*
** update
*/

void			get_rays(t_ray *ray, t_map *map, t_player *player);

/*
** utils rays
*/

bool			is_wall(t_map *map, double x, double y, t_ray *ray);
char			wall_facing(t_map *map, int x, int y, t_ray *ray);
bool			south_facing(double angle);
bool			west_facing(double angle);

/*
** utils mem
*/

void			free_game(t_game *game);
void			free_datas(t_data *datas);
void			free_map(t_map *map);

/*
** utils_others1
*/

void			free_split(char **split);
double			rad_to_deg(double radian);
double			deg_to_rad(double degree);
double			modulo_radian(double radian);
int				create_argb(int a, int r, int g, int b);

/*
** utils_others2
*/

void			check_args(int ac, char **av);
bool			check_extension(char *file, char *extension);
void			ft_realloc_protected(void **ptr, size_t orig_size,
					size_t new_size);
int				cub_next_line(int fd, char **line);
void			ft_perror(char *str);
void			ft_usage(char *str);

#endif
