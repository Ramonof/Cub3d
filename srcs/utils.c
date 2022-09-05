/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:51 by etobias           #+#    #+#             */
/*   Updated: 2022/09/05 23:29:23 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	fclamp(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

int	close_app(t_app *app)
{
	mlx_destroy_window(app->mlx, app->mlx_win);
	free_memory(app);
	exit(1);
}

double	map(double old_min, double old_max, double new_min, double new_max, double value)
{
	double	fraction;

	fraction = (value - old_min) / (old_max - old_min);
	return ((new_max - new_min) * fraction + new_min);
}
