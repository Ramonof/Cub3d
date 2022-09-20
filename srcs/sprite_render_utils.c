/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:52:48 by etobias           #+#    #+#             */
/*   Updated: 2022/09/07 02:17:17 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites(t_sprites *spr_data)
{
	size_t	i;
	int		temp;

	i = 1;
	while (i < spr_data->spr_count)
	{
		if (spr_data->spr_distance[spr_data->spr_order[i - 1]]
			< spr_data->spr_distance[spr_data->spr_order[i]])
		{
			temp = spr_data->spr_order[i - 1];
			spr_data->spr_order[i - 1] = spr_data->spr_order[i];
			spr_data->spr_order[i] = temp;
			i = 0;
		}
		++i;
	}
}

void	calc_sprite_data(t_player *player, t_sprites *spr_data, size_t i)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;

	sprite_x = spr_data->sprites[spr_data->spr_order[i]].x - player->pos_x;
	sprite_y = spr_data->sprites[spr_data->spr_order[i]].y - player->pos_y;
	inv_det = 1.0 / (player->planex * player->diry
			- player->planey * player->dirx);
	transform_x = inv_det * (player->diry * sprite_x - player->dirx * sprite_y);
	spr_data->transform_y = inv_det * (-player->planey
			* sprite_x + player->planex * sprite_y);
	spr_data->spr_screen_x = (int)((WIDTH / 2)
			* (1 + transform_x / spr_data->transform_y));
	spr_data->sprite_height = abs((int)(HEIGHT / spr_data->transform_y));
}

void	calc_sprite_borders(t_sprites *spr_data)
{
	spr_data->draw_start_y = -spr_data->sprite_height / 2 + HEIGHT / 2;
	if (spr_data->draw_start_y < 0)
		spr_data->draw_start_y = 0;
	spr_data->draw_end_y = spr_data->sprite_height / 2 + HEIGHT / 2;
	if (spr_data->draw_end_y >= HEIGHT)
		spr_data->draw_end_y = HEIGHT - 1;
	spr_data->spr_width = abs((int)(HEIGHT / spr_data->transform_y));
	spr_data->draw_start_x = -spr_data->spr_width / 2 + spr_data->spr_screen_x;
	if (spr_data->draw_start_x < 0)
		spr_data->draw_start_x = 0;
	spr_data->draw_end_x = spr_data->spr_width / 2 + spr_data->spr_screen_x;
	if (spr_data->draw_end_x >= WIDTH)
		spr_data->draw_end_x = WIDTH - 1;
}
