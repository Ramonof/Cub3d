#include "cub3d.h"

void	init_app(t_app *app)
{
	app->mlx = mlx_init();
	app->mlx_win = mlx_new_window(app->mlx, WIDTH, HEIGHT, "Cub3D");
	app->img.img = mlx_new_image(app->mlx, WIDTH, HEIGHT);
	app->img.addr = mlx_get_data_addr(app->img.img, &app->img.bits_per_pixel, &app->img.line_length,
								&app->img.endian);

	app->player.posY = 3.5;
	app->player.posX = 22.5;
	app->player.dirX = -1;
	app->player.dirY = 0;
	app->player.planeX = 0;
	app->player.planeY = -0.66;
	app->prev_mouse_x = -1;
}
