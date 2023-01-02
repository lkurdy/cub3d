/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:28:30 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/12/26 20:56:52 by rben-tkh         ###   ########.fr       */
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
		= get_color(img, start, line, img->south);
		start++;
	}
}

static void	ray_utils(t_data *img)
{
	img->step_x = 1;
	img->step_y = 1;
	img->delta_x = fabs(1 / img->ray_x);
	img->delta_y = fabs(1 / img->ray_y);
	img->side_x = (img->map_x + 1.0 - img->x) * img->delta_x;
	img->side_y = (img->map_y + 1.0 - img->y) * img->delta_y;
	if (img->ray_x < 0)
	{
		img->step_x = -1;
		img->side_x = (img->x - img->map_x) * img->delta_x;
	}
	if (img->ray_y < 0)
	{
		img->step_y = -1;
		img->side_y = (img->y - img->map_y) * img->delta_y;
	}
	if (dda(img))
	{
		if (!img->side)
			img->wall = (img->map_x - img->x + \
			(1 - img->step_x) / 2) / img->ray_x;
		else
			img->wall = (img->map_y - img->y + \
			(1 - img->step_y) / 2) / img->ray_y;
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
		new->img = mlx_xpm_file_to_image(img->mlx, img->no_path, \
		&new->width, &new->height);
	else if (x == 2)
		new->img = mlx_xpm_file_to_image(img->mlx, img->ea_path, \
		&new->width, &new->height);
	else if (x == 3)
		new->img = mlx_xpm_file_to_image(img->mlx, img->we_path, \
		&new->width, &new->height);
	else if (x == 4)
		new->img = mlx_xpm_file_to_image(img->mlx, img->so_path, \
		&new->width, &new->height);
	else
		new->img = mlx_new_image(img->mlx, width, height);
	new->buf = (int *)mlx_get_data_addr(new->img, &bpp, &x, &endian);
	return (new);
}

static int	ray(void *param)
{
	t_data	*img;
	int		y;

	img = (t_data *)param;
	img->pic = new_pic(img, img->length, img->height, 0);
	get_on_the_floor(img);
	y = -1;
	while (++y < img->length)
	{
		img->map_x = (int)img->x;
		img->map_y = (int)img->y;
		img->camera_x = 2 * y / (double)img->length - 1;
		img->ray_x = img->dir_x + img->planx * img->camera_x;
		img->ray_y = img->dir_y + img->plany * img->camera_x;
		ray_utils(img);
		draw(img, y);
	}
	mlx_put_image_to_window(img->mlx, img->win, img->pic->img, 0, 0);
	mlx_destroy_image(img->mlx, img->pic->img);
	free(img->pic);
	if (img->key && img->key == 65307)
		return (ft_close(img), 0);
	else if (img->key && img->key != 65307)
		key(img->key, img, img->dir_x);
	return (0);
}

void	display(t_data *img)
{
	img->height = 720;
	img->length = 1480;
	img->x = find_x(img->map, img);
	img->y = find_y(img->map, img);
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
