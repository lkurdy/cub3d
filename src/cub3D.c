/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:12:05 by rben-tkh          #+#    #+#             */
/*   Updated: 2023/01/04 18:03:46 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	init(char *strfd, t_data *data, char *info, int i)
{
	while (i--)
	{
		info = init_path(strfd, &data->pos, 0, &i);
		if (info && data->pos && data->pos == 'N' && !data->no_path)
			data->no_path = ft_strdup(info);
		else if (info && data->pos && data->pos == 'S' && !data->so_path)
			data->so_path = ft_strdup(info);
		else if (info && data->pos && data->pos == 'W' && !data->we_path)
			data->we_path = ft_strdup(info);
		else if (info && data->pos && data->pos == 'E' && !data->ea_path)
			data->ea_path = ft_strdup(info);
		else if (info && data->pos && data->pos == 'F' && !data->f_color)
			data->f_color = init_color(ft_strdup(info));
		else if (info && data->pos && data->pos == 'C' && !data->c_color)
			data->c_color = init_color(ft_strdup(info));
		else if (i || i == -42)
			return (write(2, "Error\nInvalid data\n", 19), free(info), -1);
		free(info);
	}
	if (!data->no_path || !data->so_path || !data->we_path || !data->ea_path
		|| !data->f_color || !data->c_color)
		return (write(2, "Error\nInvalid data\n", 19), -1);
	if (check_map(init_map(strfd, &data->map, 0, 0), &data->pos, 0, 0))
		return (write(2, "Error\nInvalid map\n", 19), -1);
	return (0);
}

static int	parsing(int ac, char **av, t_data *data, int len)
{
	char	*strfd;
	int		fd;

	if (ac != 2 || !av)
		return (write(2, "Error\nInvalid arguments\n", 24), -1);
	len = ft_strlen(av[1]);
	if (len < 4 || av[1][len - 1] != 'b' || av[1][len - 2] != 'u'
		|| av[1][len - 3] != 'c' || av[1][len - 4] != '.')
		return (write(2, "Error\nFile is not a .cub\n", 25), -1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (write(2, "Error\n", 6), perror(av[1]), -1);
	strfd = init_strfd(fd);
	if (!strfd)
	{
		write(2, "Error\n", 6);
		return (perror(av[1]), free(strfd), close(fd), -1);
	}
	if (init(strfd, data, 0, 7) || check_texture(data, 0, 0))
		return (close(fd), free(strfd), -1);
	return (close(fd), free(strfd), 0);
}

static void	display(t_data *img)
{
	img->height = 720;
	img->length = 1480;
	img->x = find_x(img->map, img);
	img->y = find_y(img->map, img);
	init_pos(img);
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

int	main(int ac, char **av)
{
	t_data	img;

	img.mlx = 0;
	img.no_path = 0;
	img.so_path = 0;
	img.we_path = 0;
	img.ea_path = 0;
	img.f_color = 0;
	img.c_color = 0;
	img.map = 0;
	img.pos = 0;
	if (parsing(ac, av, &img, 0))
	{
		img.ecode = -1;
		ft_close(&img);
	}
	img.ecode = 0;
	display(&img);
	return (0);
}
