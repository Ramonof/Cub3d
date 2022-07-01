#include "cub3d.h"

int	keyboard_input(int keycode, t_app *app)
{
    printf("Code: %i\n", keycode);
	if (keycode == D_KEY)
        app->player.posY -= SPEED;
	else if (keycode == A_KEY)
		app->player.posY += SPEED;
	else if (keycode == W_KEY)
		app->player.posX -= SPEED;
	else if (keycode == S_KEY)
		app->player.posX += SPEED;
	else if (keycode == 53)
	{
		mlx_destroy_window(app->mlx, app->mlx_win);
		exit(1);
	}
    app->player.posX = fclamp(app->player.posX, 0, 23);
    app->player.posY = fclamp(app->player.posY, 0, 23);
	render(app);
    printf("X: %f, Y: %f\n", app->player.posX, app->player.posY);
	return (0);
}
