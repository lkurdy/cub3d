#include "cub3D.h"

void	walk_check(t_data *img, double sumY, double sumX)
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

t_pic	*new_pic(t_data *img, int width, int height, int x)
{
	t_pic	*new;
	int		trsh;
	int		bpp;
	int		endian;

	bpp = 32;
	endian = 1;
	new = malloc(sizeof(t_pic));
	new->width = width;
	new->height = height;
	if (x == 1)
		new->img = mlx_xpm_file_to_image(img->mlx, img->NO_path, &new->width, &new->height);
	else if (x == 2)
		new->img = mlx_xpm_file_to_image(img->mlx, img->EA_path, &new->width, &new->height);
	else if (x == 3)
		new->img = mlx_xpm_file_to_image(img->mlx, img->WE_path, &new->width, &new->height);
	else if (x == 4)
		new->img = mlx_xpm_file_to_image(img->mlx, img->SO_path, &new->width, &new->height);
	else
		new->img = mlx_new_image(img->mlx, width, height);
	new->buf = (int*)mlx_get_data_addr(new->img, &bpp, &trsh, &endian);
	return (new);
}

t_pic	*texture(t_data *img)
{
	if (img->rayX > 0 && img->side)
		return (img->west);
	if (img->rayX < 0 && img->side)
		return (img->east);
	if (img->rayY < 0 && !img->side)
		return (img->south);
	return (img->north);
}

int	get_color(t_data *img, float start, int line)
{
	int		color;
	double	x_text;
	double	x_wall;
	double	y_text;
	t_pic	*t;

	t = texture(img);
	if (img->side == 0)
		x_wall = img->Y + img->wall * img->rayY;
	else
		x_wall = img->X + img->wall * img->rayX;
	x_wall -= floor((x_wall));
	x_text = (int)(x_wall * (double)(t->width));
	if (img->side == 0 && img->rayX > 0)
		x_text = t->width - x_text - 1;
	if (img->side == 1 && img->rayY < 0)
		x_text = t->width - x_text - 1;
	color = start * 256 - img->height * 128 + line * 128;
	y_text = ((color * t->height) / line) / 256;
	color = t->buf[(int)(y_text * t->width + x_text)];
	return (color);
}
