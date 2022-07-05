#ifndef CUB3D_H

# define CUB3D_H

# include <fcntl.h>
# include "get_next_line.h"
# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <errno.h>

# define WIDTH 1280
# define HEIGHT 720

# define SPEED 0.2
# define ROT_SPEED 0.06

# define MAP_SET " 01NSEW"

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

typedef struct	s_textures {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color	f;
	t_color	c;
	char	**map;
	int		map_w;
	int		map_h;
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

typedef struct s_app
{
	void		*mlx;			// mlx
	void		*mlx_win;		// mlx window
	t_data		img;			// image data
	t_player	player;			// player data
	char		**map;			// level map
	int			prev_mouse_x;	// prev mouse X position
	t_textures	*textures;
}	t_app;

/* init.c */
void	init_app(t_app *app);

/* render.c */
void	render(t_app *app);

/* graphics_utils.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

/* controls.c */
int		keyboard_input(int keycode, t_app *app);
int 	mouse_move(int x, int y, t_app *app);

/* utils.c */
double  fclamp(double value, double min, double max);
int		close_app(t_app *app);

/* errors.c*/
void	error_exit(char *err);
void	errno_exit(char *err);

/* textures_utils.c */
void	print_textures_data(t_textures *textures);
void	free_textures_data(t_textures *textures);
void	init_textures(t_textures *textures);

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

#endif