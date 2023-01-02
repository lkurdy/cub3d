/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:12:13 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/12/26 20:56:52 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	press(int keycode, t_data *img)
{
	img->key = 0;
	img->key = keycode;
	return (0);
}

int	release(int keycode, t_data *img)
{
	(void)keycode;
	img->key = 0;
	return (0);
}

void	get_pos(t_data *img)
{
	img->dir_x = 0;
	img->dir_y = -1;
	img->planx = 0.66;
	img->plany = 0;
	if (img->pos == 'E')
	{
		img->dir_x = 1;
		img->dir_y = 0;
		img->planx = 0;
		img->plany = 0.66;
	}
	else if (img->pos == 'W')
	{
		img->dir_x = -1;
		img->dir_y = 0;
		img->planx = 0;
		img->plany = -0.66;
	}
	else if (img->pos == 'S')
	{
		img->dir_x = 0;
		img->dir_y = 1;
		img->planx = -0.66;
		img->plany = 0;
	}
}

void	get_on_the_floor(t_data *img)
{
	int	i;

	i = 0;
	while (i < (img->length * img->height) / 2)
	{
		img->pic->buf[i] = img->c_color[0] << 16;
		img->pic->buf[i] += img->c_color[1] << 8;
		img->pic->buf[i] += img->c_color[2];
		i++;
	}
	while (i < img->length * img->height)
	{
		img->pic->buf[i] = img->f_color[0] << 16;
		img->pic->buf[i] += img->f_color[1] << 8;
		img->pic->buf[i] += img->f_color[2];
		i++;
	}
}

int	get_color(t_data *img, float start, int line, t_pic *texture)
{
	int		color;
	double	x_text;
	double	x_wall;
	double	y_text;

	if (img->ray_x > 0 && !img->side)
		texture = img->east;
	if (img->ray_x < 0 && !img->side)
		texture = img->west;
	if (img->ray_y < 0 && img->side)
		texture = img->north;
	if (img->side == 0)
		x_wall = img->y + img->wall * img->ray_y;
	else
		x_wall = img->x + img->wall * img->ray_x;
	x_wall -= floor((x_wall));
	x_text = (int)(x_wall * (double)(texture->width));
	if (img->side == 0 && img->ray_x > 0)
		x_text = texture->width - x_text - 1;
	if (img->side == 1 && img->ray_y < 0)
		x_text = texture->width - x_text - 1;
	color = start * 256 - img->height * 128 + line * 128;
	y_text = ((color * texture->height) / line) / 256;
	color = texture->buf[(int)(y_text * texture->width + x_text)];
	return (color);
}
