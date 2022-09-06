/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:21:59 by mrolande          #+#    #+#             */
/*   Updated: 2022/09/06 10:21:59 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include <fcntl.h>
# include "get_next_line.h"
# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <errno.h>
# include <stdbool.h>
# include <limits.h>

# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define E_KEY 101

# define WIDTH 1280
# define HEIGHT 720

# define SPEED 0.2
# define ROT_SPEED 0.06

# ifndef MAP_SET
#  define MAP_SET "D 01NSEW"
# endif

# define SPRITE_PATH "textures/pillar.xpm"
# define DOOR_PATH "textures/door.xpm"

# define CH_WALL '1'
# define CH_CLOSED_DOOR 'D'
# define CH_OPEN_DOOR 'C'

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_color {
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_sprite
{
	double	x;
	double	y;
}	t_sprite;

typedef struct	s_textures {
	char	*no;			// walls' texture directories
	char	*so;
	char	*ea;
	char	*we;
	int		size;			// textures' size
	void	*n_image;		// walls' texture images
	void	*s_image;
	void	*e_image;
	void	*w_image;
	char	*n_texture;		// walls' texture data
	char	*s_texture;
	char	*e_texture;
	char	*w_texture;
	t_color	f;				// floor color
	t_color	c;				// ceiling color
	char	**map;			// map data
	int		map_w;			// map width
	int		map_h;			// map height
	void	*sprite_image;
	char	*sprite_texture;
	void	*door_image;
	char	*door_texture;
}	t_textures;

typedef struct s_player
{
	double	posX;	// X position
	double	posY;	// Y position
	double	dirX;	// X look direction
	double	dirY;	// Y look direction
	double	planeX; // X camera plane direction
	double	planeY; // Y camera plane direction
}	t_player;

typedef struct	s_minimap
{
	int	min_x;
	int	min_y;
	int	max_x;
	int	max_y;
	int	radius;
	int	scale;
	int	map_x;
	int	map_y;
}	t_minimap;

typedef struct s_sprites
{
	size_t		spr_count;
	t_sprite	*sprites;
	int			*spr_order;
	double		*spr_distance;
	double		transform_y;
	int			spr_screen_x;
	int			sprite_height;
	int			draw_start_y;
	int			draw_end_y;
	int			draw_start_x;
	int			draw_end_x;
	int			spr_width;
	int			tex_x;
	int			stripe;
}	t_sprites;


typedef struct s_app
{
	void		*mlx;			// mlx
	void		*mlx_win;		// mlx window
	t_data		img;			// image data
	t_player	player;			// player data
	char		**map;			// level map
	t_sprites	sprites_data;
	int			prev_mouse_x;	// prev mouse X position
	t_textures	*textures;
	bool		update;			// flag to update the screen image
	double		z_buffer[WIDTH];
	t_minimap	minimap;
}	t_app;

typedef struct s_ray
{
	int		screen_x;
	double 	camera_x;
	double 	ray_dir_x;
	double 	ray_dir_y;
	int		draw_start;
	int		draw_end;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	double	step;
	double	tex_pos;
}	t_ray;

/* init.c */
void	init_app(t_app *app);

/* render.c */
void	render(t_app *app);

/* graphics_utils.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		create_argb(int a, int r, int g, int b);

/* controls.c */
int		keyboard_input(int keycode, t_app *app);
int 	mouse_move(int x, int y, t_app *app);

/* utils.c */
double  fclamp(double value, double min, double max);
int		close_app(t_app *app);
double	map(double old_min, double old_max, double new_min, double new_max, double value);

/* errors.c*/
void	error_exit(char *err);
void	errno_exit(char *err);

/* textures_utils.c */
void	print_textures_data(t_textures *textures);
void	free_textures_data(t_textures *textures);
void	init_textures(t_textures *textures);
int		get_text_x(t_app *app, t_ray *ray, int side, double wall_dist);
void	get_line_borders(t_ray *ray, int side);

/* parser.c */
void	start_parse(char *map_name, t_textures *textures);

/* map_parser.c */
int		get_map_info(int fd, t_textures *textures, char *line, int *code);
int		in_set(char c, const char *set);

/* get_map.c */
void    get_map(t_textures *textures, int iter, int fd, char *line);

/* check_map.c */
void	check_map(t_textures *textures);

/* parse_utils.c */
void	parse_end(char *line);
int		in_set(char c, const char *set);
void	fill_arr_util(char *info, char *line);

/* parse_utils_utils.c */
int		my_atoi(char *str);
void	valid_color(char *str, int num);
int		fill_g(t_color *info, char *line, int nbr);
int		fill_b(t_color *info, char *line, int nbr);
int		fill_r(t_color *info, char *line, int nbr);

/* render_utils.c */
double	get_wall_dist(t_ray *ray, int side);
char    *get_texture(t_app *app, t_ray *ray, int side);
int		cast_ray(t_app *app, t_ray *ray);
void	calc_ray_side_dist(t_player *player, t_ray *ray);

/* free_memory.c */
void	free_memory(t_app *app);

/* sprite_render.c */
void    draw_sprites(t_app *app);

/* sprite_render_utils.c */
void	sort_sprites(t_sprites *spr_data);
void	calc_sprite_data(t_player *player, t_sprites *sprites_data, size_t i);
void    calc_sprite_borders(t_sprites *sprites_data);

/* minimap_render.c */
void	draw_minimap(t_app *app);

/* controls_utils.c */
void    door_interaction(t_app *app);
void	move_player(t_app *app, double x_dir, double y_dir);
void	rotate_camera(t_app *app, int direction);

/* init_utils.c */
void    load_wall_textures(t_app *app);

#endif