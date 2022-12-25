/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:28:30 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/12/24 11:28:30 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw(t_data *img, int x)
{
	int	line;
	int	start;
	int	end;

	if (img->wall < 0)
		return ;
	line = (int)(img->height / img->wall);
	if (line > 200000)
		line = 200000;
	start = -line / 2 + img->height / 2;
	if (start < 0)
		start = 0;
	end = line / 2 + img->height / 2;
	if (end >= img->height)
		end = img->height - 1;
	while (start < end)
	{
		img->pic->buf[(img->pic->width * start) + x] \
		= get_color(img, start, line, img->north);
		start++;
	}
}

static void	ray_utils(t_data *img)
{
	img->stepX = 1;
	img->stepY = 1;
	img->deltaX = fabs(1 / img->rayX);
	img->deltaY = fabs(1 / img->rayY);
	img->sideX = (img->mapX + 1.0 - img->X) * img->deltaX;
	img->sideY = (img->mapY + 1.0 - img->Y) * img->deltaY;
	if (img->rayX < 0)
	{
		img->stepX = -1;
		img->sideX = (img->X - img->mapX) * img->deltaX;
	}
	if (img->rayY < 0)
	{
		img->stepY = -1;
		img->sideY = (img->Y - img->mapY) * img->deltaY;
	}
	if (DDA(img))
	{
		if (!img->side)
			img->wall = (img->mapX - img->X + \
			(1 - img->stepX) / 2) / img->rayX;
		else
			img->wall = (img->mapY - img->Y + \
			(1 - img->stepY) / 2) / img->rayY;
	}
}

static t_pic	*new_pic(t_data *img, int width, int height, int x)
{
	t_pic	*new;
	int		bpp;
	int		endian;

	bpp = 32;
	endian = 1;
	new = malloc(sizeof(t_pic));
	new->width = width;
	new->height = height;
	if (x == 1)
		new->img = mlx_xpm_file_to_image(img->mlx, img->NO_path, \
		&new->width, &new->height);
	else if (x == 2)
		new->img = mlx_xpm_file_to_image(img->mlx, img->EA_path, \
		&new->width, &new->height);
	else if (x == 3)
		new->img = mlx_xpm_file_to_image(img->mlx, img->WE_path, \
		&new->width, &new->height);
	else if (x == 4)
		new->img = mlx_xpm_file_to_image(img->mlx, img->SO_path, \
		&new->width, &new->height);
	else
		new->img = mlx_new_image(img->mlx, width, height);
	new->buf = (int*)mlx_get_data_addr(new->img, &bpp, &x, &endian);
	return (new);
}

static int	ray(void *param)
{
	t_data	*img;
	int		y;

	img = (t_data*)param;
	img->pic = new_pic(img, img->length, img->height, 0);
	get_on_the_floor(img);
	y = -1;
	while (++y < img->length)
	{
		img->mapX = (int)img->X;
		img->mapY = (int)img->Y;
		img->cameraX = 2 * y / (double)img->length - 1;
		img->rayX = img->dirX + img->planX * img->cameraX;
		img->rayY = img->dirY + img->planY * img->cameraX;
		ray_utils(img);
		draw(img, y);
	}
	mlx_put_image_to_window(img->mlx, img->win, img->pic->img, 0, 0);
	mlx_destroy_image(img->mlx, img->pic->img);
	free(img->pic);
	if (img->key && img->key == 65307)
		return (ft_close(img), 0);
	else if (img->key && img->key != 65307)
		key(img->key, img, img->dirX);
	return (0);
}

void	display(t_data *img)
{
	img->height = 720;
	img->length = 1480;
	img->X = find_x(img->map, img);
	img->Y = find_y(img->map, img);
	get_pos(img);
	img->key = 0;
	img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx, img->length, img->height, "cub3D");
	img->north = new_pic(img, 0, 0, 1);
	img->east = new_pic(img, 0, 0, 2);
	img->west = new_pic(img, 0, 0, 3);
	img->south = new_pic(img, 0, 0, 4);
	mlx_hook(img->win, 2, 1L << 0, &press, img);
	mlx_hook(img->win, 3, 1L << 1, &release, img);
	mlx_hook(img->win, 17, 0, ft_close, img);
	mlx_loop_hook(img->mlx, &ray, img);
	mlx_loop(img->mlx);
}
