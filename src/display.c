/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:28:30 by rben-tkh          #+#    #+#             */
/*   Updated: 2023/01/04 18:05:02 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	put_texture(t_data *img, float start, int line, t_pic *texture)
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
		= put_texture(img, start, line, img->south);
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

t_pic	*new_pic(t_data *img, int width, int height, int x)
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

int	ray(void *param)
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
		ft_close(img);
	else if (img->key && img->key != 65307)
		key(img->key, img, img->dir_x);
	return (0);
}
