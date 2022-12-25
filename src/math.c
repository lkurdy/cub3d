/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:30:27 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/12/24 11:30:28 by rben-tkh         ###   ########.fr       */
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

int	DDA(t_data *img)
{
	while (1)
	{
		if (img->sideX < img->sideY)
		{
			img->sideX += img->deltaX;
			img->mapX += img->stepX;
			img->side = 0;
		}
		else
		{
			img->sideY  += img->deltaY;
			img->mapY += img->stepY;
			img->side = 1;
		}
		if (img->mapY < 0)
			img->mapY = 0;
		if (img->mapX < 0)
			img->mapX = 0;
		if (!img->map[img->mapY] || !img->map[img->mapY][img->mapX])
			return (img->wall = -1, 0);
		if (img->map[img->mapY][img->mapX] == '1')
			return (1);
	}
	return (0);
}

static void	walk_check(t_data *img, double sumY, double sumX)
{
	if ((int)sumY >= 0 && img->map[(int)sumY])
	{
		img->Y = sumY;
		if ((int)sumX >= 0 && img->map[(int)sumY][(int)sumX])
		{
			img->X = sumX;
		}
	}
}

void	key(int keycode, t_data *img, double temp)
{
	if (keycode == 'W' || keycode == 'w')
		walk_check(img, img->Y + img->dirY * 0.05 , img->X + img->dirX * 0.05);
	else if (keycode == 'S' || keycode == 's')
		walk_check(img, img->Y - img->dirY * 0.05, img->X - img->dirX * 0.05);
	else if (keycode == 'A' || keycode == 'a')
		walk_check(img, img->Y - img->planY * 0.05, img->X - img->planX * 0.05);
	else if (keycode == 'D' || keycode == 'd')
		walk_check(img, img->Y + img->planY * 0.05, img->X + img->planX * 0.05);
	if (keycode == 65361 || keycode == 'o')
	{
		img->dirX = img->dirX * cos(-0.02) - img->dirY * sin(-0.02);
		img->dirY = temp * sin(-0.02) + img->dirY * cos(-0.02);
		temp = img->planX;
		img->planX = img->planX * cos(-0.02) - img->planY * sin(-0.02);
		img->planY = temp * sin(-0.02) + img->planY * cos(-0.02);
	}
	else if (keycode == 65363 || keycode == 'p')
	{
		img->dirX = img->dirX * cos(0.02) - img->dirY * sin(0.02);
		img->dirY = temp * sin(0.02) + img->dirY * cos(0.02);
		temp = img->planX;
		img->planX = img->planX * cos(0.02) - img->planY * sin(0.02);
		img->planY = temp * sin(0.02) + img->planY * cos(0.02);
	}
}
