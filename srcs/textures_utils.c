/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 00:55:49 by mrolande          #+#    #+#             */
/*   Updated: 2022/07/26 02:16:58 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures_data(t_textures *textures)
{
	int	i;

	free(textures->no);
	free(textures->so);
	free(textures->we);
	free(textures->ea);
	i = 0;
	while (i < textures->map_h)
	{
		free(textures->map[i]);
		i++;
	}
	free(textures->map);
	get_next_line(0, NULL, 1);
}

void	init_textures(t_textures *textures)
{
	textures->no = NULL;
	textures->so = NULL;
	textures->we = NULL;
	textures->ea = NULL;
	textures->f.r = -1;
	textures->c.r = -1;
	textures->map_w = 0;
	textures->map_h = 0;
}
