#include "cub3d.h"

double  fclamp(double value, double min, double max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

int	close_app(t_app *app)
{
	mlx_destroy_window(app->mlx, app->mlx_win);
	exit(1);
}
