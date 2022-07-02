/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 00:55:49 by mrolande          #+#    #+#             */
/*   Updated: 2022/07/02 00:55:49 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_textures_data(t_textures *textures)
{
	int i = 0, j;
	ft_putstr_fd("NO ", 1);
	ft_putendl_fd(textures->no, 1);
	ft_putstr_fd("SO ", 1);
	ft_putendl_fd(textures->so, 1);
	ft_putstr_fd("WE ", 1);
	ft_putendl_fd(textures->we, 1);
	ft_putstr_fd("EA ", 1);
	ft_putendl_fd(textures->ea, 1);
	printf("F %d,%d,%d\n", textures->f.r, textures->f.g, textures->f.b);
	printf("C %d,%d,%d\n", textures->c.r, textures->c.g, textures->c.b);
	printf("w %d h %d\n", textures->map_w, textures->map_h);
	while (i < textures->map_h)
	{
		j = 0;
		while (j < textures->map_w)
		{
			printf("%c", textures->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

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