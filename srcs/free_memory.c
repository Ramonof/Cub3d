/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:55:34 by etobias           #+#    #+#             */
/*   Updated: 2022/09/05 23:38:20 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_memory(t_app *app)
{
	mlx_destroy_image(app->mlx, app->textures->n_image);
	mlx_destroy_image(app->mlx, app->textures->s_image);
	mlx_destroy_image(app->mlx, app->textures->e_image);
	mlx_destroy_image(app->mlx, app->textures->w_image);
	mlx_destroy_image(app->mlx, app->textures->sprite_image);
	mlx_destroy_image(app->mlx, app->textures->door_image);
	free(app->sprites_data.sprites);
	free_textures_data(app->textures);
	mlx_destroy_image(app->mlx, app->img.img);
	mlx_destroy_display(app->mlx); //remove on macos
	free(app->mlx);
}
