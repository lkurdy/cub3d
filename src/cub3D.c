/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:12:05 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/12/26 20:53:53 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	if (init_data(strfd, data, 0, 6) || check_path(data, 0, 0))
		return (close(fd), free(strfd), -1);
	return (close(fd), free(strfd), 0);
}

int	main(int argc, char **argv)
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
	if (parsing(argc, argv, &img, 0))
		return (ft_close(&img), -1);
	display(&img);
	return (0);
}
