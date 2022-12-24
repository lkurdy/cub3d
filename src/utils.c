/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:12:13 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/12/22 15:12:14 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_pos(t_data *img)
{
	img->dirX = 0;
	img->dirY = -1;
	img->planX = 0.66;
	img->planY = 0;
	if (img->pos == 'E')
	{
		img->dirX = 1;
		img->dirY = 0;
		img->planX = 0;
		img->planY = 0.66;
	}
	else if (img->pos == 'W')
	{
		img->dirX = -1;
		img->dirY = 0;
		img->planX = 0;
		img->planY = -0.66;
	}
	else if (img->pos == 'S')
	{
		img->dirX = 0;
		img->dirY = 1;
		img->planX = -0.66;
		img->planY = 0;
	}
}

void	get_on_the_floor(t_data *img)
{
	int	i;

	i = 0;
	while (i < (img->length * img->height) / 2)
	{
		img->pic->buf[i] = img->C_color[0] << 16;
		img->pic->buf[i] += img->C_color[1] << 8;
		img->pic->buf[i] += img->C_color[2];
		i++;
	}
	while (i < img->length * img->height)
	{
		img->pic->buf[i] = img->F_color[0] << 16;
		img->pic->buf[i] += img->F_color[1] << 8;
		img->pic->buf[i] += img->F_color[2];
		i++;
	}
}

int	get_color(t_data *img, float start, int line, t_pic	*texture)
{
	int		color;
	double	x_text;
	double	x_wall;
	double	y_text;

	if (img->rayX > 0 && img->side)
		texture = img->west;
	if (img->rayX < 0 && img->side)
		texture = img->east;
	if (img->rayY < 0 && !img->side)
		texture = img->south;
	if (img->side == 0)
		x_wall = img->Y + img->wall * img->rayY;
	else
		x_wall = img->X + img->wall * img->rayX;
	x_wall -= floor((x_wall));
	x_text = (int)(x_wall * (double)(texture->width));
	if (img->side == 0 && img->rayX > 0)
		x_text = texture->width - x_text - 1;
	if (img->side == 1 && img->rayY < 0)
		x_text = texture->width - x_text - 1;
	color = start * 256 - img->height * 128 + line * 128;
	y_text = ((color * texture->height) / line) / 256;
	color = texture->buf[(int)(y_text * texture->width + x_text)];
	return (color);
}
