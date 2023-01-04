/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:12:13 by rben-tkh          #+#    #+#             */
/*   Updated: 2023/01/03 18:34:14 by rben-tkh         ###   ########.fr       */
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
