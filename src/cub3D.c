/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 06:57:16 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/12/12 06:57:19 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_error(int ac, char **av, char *file, t_data *data)
{
	int	len;
	int	fd;

	if (ac != 2 || !av)
		return (write(2, "Error\nInvalid arguments\n", 24), -1);
	len = ft_strlen(file);
	if (len < 5 || file[len - 1] != 'b' || file[len - 2] != 'u'
		|| file[len - 3] != 'c' || file[len - 4] != '.')
		return (write(2, "Error\nFile is not a .cub\n", 26), -1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (close(fd), write(2, "Error\n", 6), perror(NULL), -1);
	if (init_data(fd, data))
		return (close(fd), -1);
	return (close(fd), 0);
}

int main(int ac, char **av)
{
	t_data	data;

	if (check_error(ac, av, av[1], &data))
		return (-1);
	return (0);
}
