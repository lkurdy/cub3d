#include "cub3D.h"

int	ft_close(t_data *img)
{
//	mlx_destroy_image(img->mlx, img->pic->img);
	mlx_destroy_image(img->mlx, img->north->img);
	mlx_destroy_image(img->mlx, img->east->img);
	mlx_destroy_image(img->mlx, img->west->img);
	mlx_destroy_image(img->mlx, img->south->img);
	mlx_destroy_window(img->mlx, img->win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	free(img->north);
	free(img->east);
	free(img->west);
	free(img->south);
//	free(img->pic);
	ft_free(img->map);
	exit (0);
}

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

void	init_stuff(t_data *img)
{
	if (img->pos == 'N')
	{
		img->dirX = 0;
		img->dirY = -1;
		img->planX = 0.66;
		img->planY = 0;
	}
	else if (img->pos == 'E')
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

void	put_map(t_data *img)
{
	img->X = find_x(img->map, img);
	img->Y = find_y(img->map, img);
	init_stuff(img);
	img->key = 0;
}

void	DDA(t_data *img)
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
		{
			img->wall = -1;
			return ;
		}
		if (img->map[img->mapY][img->mapX] == '1')
			break ;
	}
	if (!img->side)
		img->wall = (img->mapX - img->X + (1 - img->stepX) / 2) / img->rayX;
	else
		img->wall = (img->mapY - img->Y + (1 - img->stepY) / 2) / img->rayY;
}

void	draw(t_data *img, int x)
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
		img->pic->buf[(img->pic->width * start) + x] = get_color(img, start, line);
		start++;
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

int	ray(void *param)
{
	t_data	*img;

	img = (t_data*)param;
	img->pic = new_pic(img, img->length, img->height, 0);
	get_on_the_floor(img);
	for(int y = 0; y < img->length ; y++)
	{
		img->mapX = (int)img->X;
		img->mapY = (int)img->Y;
		img->cameraX = 2 * y / (double)img->length - 1;
		img->rayX = img->dirX + img->planX * img->cameraX;
		img->rayY = img->dirY + img->planY * img->cameraX;
		img->deltaX = fabs(1 / img->rayX);
		img->deltaY = fabs(1 / img->rayY);
		if (img->rayX < 0)
		{
			img->stepX = -1;
			img->sideX = (img->X - img->mapX) * img->deltaX;
		}
		else
		{
			img->stepX = 1;
			img->sideX = (img->mapX + 1.0 - img->X) * img->deltaX;
		}
		if (img->rayY < 0)
		{
			img->stepY = -1;
			img->sideY = (img->Y - img->mapY) * img->deltaY;
		}
		else
		{
			img->stepY = 1;
			img->sideY = (img->mapY + 1.0 - img->Y) * img->deltaY;
		}
		DDA(img);
		draw(img, y);
	}
	mlx_put_image_to_window(img->mlx, img->win, img->pic->img, 0, 0);
	mlx_destroy_image(img->mlx, img->pic->img);
	free(img->pic);
	if (img->key)
		key(img->key, img);
	return (0);
}

void	key(int keycode, t_data *img)
{
	double	temp;

	if (keycode == 65307)
		ft_close(img);
	else if (keycode == 'W' || keycode == 'w')
		walk_check(img, img->Y + img->dirY * 0.05 , img->X + img->dirX * 0.05);
	else if (keycode == 'S' || keycode == 's')
		walk_check(img, img->Y - img->dirY * 0.05, img->X - img->dirX * 0.05);
	else if (keycode == 'A' || keycode == 'a')
		walk_check(img, img->Y - img->planY * 0.05, img->X - img->planX * 0.05);
	else if (keycode == 'D' || keycode == 'd')
		walk_check(img, img->Y + img->planY * 0.05, img->X + img->planX * 0.05);
	if (keycode == 65361 || keycode == 'o')
	{
		temp = img->dirX;
		img->dirX = img->dirX * cos(-0.02) - img->dirY * sin(-0.02);
		img->dirY = temp * sin(-0.02) + img->dirY * cos(-0.02);
		temp = img->planX;
		img->planX = img->planX * cos(-0.02) - img->planY * sin(-0.02);
		img->planY = temp * sin(-0.02) + img->planY * cos(-0.02);
	}
	else if (keycode == 65363 || keycode == 'p')
	{
		temp = img->dirX;
		img->dirX = img->dirX * cos(0.02) - img->dirY * sin(0.02);
		img->dirY = temp * sin(0.02) + img->dirY * cos(0.02);
		temp = img->planX;
		img->planX = img->planX * cos(0.02) - img->planY * sin(0.02);
		img->planY = temp * sin(0.02) + img->planY * cos(0.02);
	}
}

int	press(int keycode, t_data *img)
{
	img->key = 0;
	img->key = keycode;
	return (0);
}

int	release(int keycode, t_data *img)
{
	img->key = 0;
	return (keycode - keycode);
}

int	main(int argc, char **argv)
{
	t_data	img;

	if (check_error(argc, argv, &img))
		return (-1);
	img.height = 720;
	img.length = 1480;
	img.X = find_x(img.map, &img);
	img.Y = find_y(img.map, &img);
	init_stuff(&img);
	img.key = 0;
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, img.length, img.height, "Cub3d");
	img.north = new_pic(&img, 0, 0, 1);
	img.east = new_pic(&img, 0, 0, 2);
	img.west = new_pic(&img, 0, 0, 3);
	img.south = new_pic(&img, 0, 0, 4);
	mlx_hook(img.win, 2, 1L << 0, &press, &img);
	mlx_hook(img.win, 3, 1L << 1, &release, &img);
	mlx_hook(img.win, 17, 0, ft_close, &img);
	mlx_loop_hook(img.mlx, &ray, &img);
	mlx_loop(img.mlx);
	return (0);
}
