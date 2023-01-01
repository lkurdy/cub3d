/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:30:27 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/12/26 20:56:52 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	find_x(char **map, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != img->pos)
			j++;
		if (map[i][j] && map[i][j] == img->pos)
			return (j + 0.5);
		i++;
	}
	return (0);
}

double	find_y(char **map, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != img->pos)
			j++;
		if (map[i][j] && map[i][j] == img->pos)
			return (i + 0.5);
		i++;
	}
	return (0);
}

int	dda(t_data *img)
{
	while (1)
	{
		if (img->side_x < img->side_y)
		{
			img->side_x += img->delta_x;
			img->map_x += img->step_x;
			img->side = 0;
		}
		else
		{
			img->side_y += img->delta_y;
			img->map_y += img->step_y;
			img->side = 1;
		}
		if (img->map_y < 0)
			img->map_y = 0;
		if (img->map_x < 0)
			img->map_x = 0;
		if (!img->map[img->map_y] || !img->map[img->map_y][img->map_x]
				|| img->map[img->map_y][img->map_x] == ' ')
			return (img->wall = -1, 0);
		if (img->map[img->map_y][img->map_x] == '1')
			return (1);
	}
	return (0);
}

static void	walk_check(t_data *img, double sumy, double sumX)
{
	if ((int)sumy >= 0 && img->map[(int)sumy])
	{
		img->y = sumy;
		if ((int)sumX >= 0 && img->map[(int)sumy][(int)sumX]
				&& img->map[(int)sumy][(int)sumX] != ' ')
			img->x = sumX;
	}
}

void	key(int keycode, t_data *img, double temp)
{
	if (keycode == 'W' || keycode == 'w')
		walk_check(img, img->y + img->dir_y * 0.05, img->x + img->dir_x * 0.05);
	else if (keycode == 'S' || keycode == 's')
		walk_check(img, img->y - img->dir_y * 0.05, img->x - img->dir_x * 0.05);
	else if (keycode == 'A' || keycode == 'a')
		walk_check(img, img->y - img->plany * 0.05, img->x - img->planx * 0.05);
	else if (keycode == 'D' || keycode == 'd')
		walk_check(img, img->y + img->plany * 0.05, img->x + img->planx * 0.05);
	if (keycode == 65361 || keycode == 'o')
	{
		img->dir_x = img->dir_x * cos(-0.02) - img->dir_y * sin(-0.02);
		img->dir_y = temp * sin(-0.02) + img->dir_y * cos(-0.02);
		temp = img->planx;
		img->planx = img->planx * cos(-0.02) - img->plany * sin(-0.02);
		img->plany = temp * sin(-0.02) + img->plany * cos(-0.02);
	}
	else if (keycode == 65363 || keycode == 'p')
	{
		img->dir_x = img->dir_x * cos(0.02) - img->dir_y * sin(0.02);
		img->dir_y = temp * sin(0.02) + img->dir_y * cos(0.02);
		temp = img->planx;
		img->planx = img->planx * cos(0.02) - img->plany * sin(0.02);
		img->plany = temp * sin(0.02) + img->plany * cos(0.02);
	}
}
