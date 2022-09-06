/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 23:36:40 by etobias           #+#    #+#             */
/*   Updated: 2022/09/05 23:41:27 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_wall_textures(t_app *app)
{
	t_textures	*textures;
	int			size;

	textures = app->textures;
	size = textures->size;
	textures->n_image = mlx_xpm_file_to_image(app->mlx,
			textures->no, &size, &size);
	if (!textures->n_image)
		error_exit("MLX: Bad wall N");
	textures->n_texture = mlx_get_data_addr(textures->n_image,
			&size, &size, &size);
	textures->s_image = mlx_xpm_file_to_image(app->mlx,
			textures->so, &size, &size);
	if (!textures->s_image)
		error_exit("MLX: Bad wall S");
	textures->s_texture = mlx_get_data_addr(textures->s_image,
			&size, &size, &size);
	textures->e_image = mlx_xpm_file_to_image(app->mlx,
			textures->ea, &size, &size);
	if (!textures->n_image)
		error_exit("MLX: Bad wall E");
	textures->e_texture = mlx_get_data_addr(textures->e_image,
			&size, &size, &size);
	textures->w_image = mlx_xpm_file_to_image(app->mlx,
			textures->we, &size, &size);
	if (!textures->n_image)
		error_exit("MLX: Bad wall W");
	textures->w_texture = mlx_get_data_addr(textures->w_image,
			&size, &size, &size);
}
