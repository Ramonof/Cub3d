#include "cub3d.h"

void render(t_app *app)
{
	t_player *player = &app->player;

	for (int x = 0; x < WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = player->dirX + player->planeX * cameraX;
		double rayDirY = player->dirY + player->planeY * cameraX;

		int mapX = (int)player->posX;
		int mapY = (int)player->posY;

		double sideDistX;
		double sideDistY;

		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
	  	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
	  	double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player->posY) * deltaDistY;
		}

		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
				else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (app->map[mapX][mapY] > 0)
				hit = 1;
		}

		if (!side)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		
		int lineHeight = (int)(HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		int color;
		switch(app->map[mapX][mapY])
		{
			case 1: color = 0xe34040; break;
			case 2: color = 0x7592f0; break;
			case 3: color = 0xf78a5c; break;
			case 4: color = 0xcfa8e6; break;
			default: color = 0x00FF0020; break;
		}
		
		if (side == 1)
			color /= 2;

		for (int y = 0; y < drawStart; y++)
			my_mlx_pixel_put(&app->img, x, y, 0xa8e6d5);
		for (int y = drawStart; y < drawEnd; y++)
			my_mlx_pixel_put(&app->img, x, y, color);
		for (int y = drawEnd; y < HEIGHT; y++)
			my_mlx_pixel_put(&app->img, x, y, 0x6e6e6e);
	}

	mlx_put_image_to_window(app->mlx, app->mlx_win, app->img.img, 0, 0);
}
