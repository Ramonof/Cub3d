#include "cub3d.h"

void	free_memory(t_app *app)
{
	mlx_destroy_image(app->mlx, app->textures->n_image);
	mlx_destroy_image(app->mlx, app->textures->s_image);
	mlx_destroy_image(app->mlx, app->textures->e_image);
	mlx_destroy_image(app->mlx, app->textures->w_image);
	free_textures_data(app->textures);
}
