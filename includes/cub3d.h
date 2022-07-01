#ifndef CUB3D_H

# define CUB3D_H

# include <fcntl.h>
# include "get_next_line.h"
# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <stdio.h>

# define WIDTH 1280
# define HEIGHT 720

# define SPEED 0.2
# define ROT_SPEED 0.06

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define ESC_KEY 65307

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

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
	int			**map;			// level map
	int			prev_mouse_x;	// prev mouse X position
}	t_app;

/* render.c */
void render(t_app *app);

/* graphics_utils.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

/* controls.c */
int		keyboard_input(int keycode, t_app *app);
int 	mouse_move(int x, int y, t_app *app);

/* utils.c */
double  fclamp(double value, double min, double max);

#endif