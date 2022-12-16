/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:17:13 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/12/15 18:17:15 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_id(char *str, int i, char c)
{
	if (c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != 'F' && c != 'C')
		return (-1);
	else if (c == 'N' && str[i] && str[i] != 'O')
		return (-1);
	else if (c == 'S' && str[i] && str[i] != 'O')
		return (-1);
	else if (c == 'W' && str[i] && str[i] != 'E')
		return (-1);
	else if (c == 'E' && str[i] && str[i] != 'A')
		return (-1);
	else if ((c == 'N' || c == 'S' || c == 'W' || c == 'E')
		&& str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '\t')
		return (-1);
	else if ((c == 'F' || c == 'C')
		&& str[i] && str[i] != ' ' && str[i] != '\t')
		return (-1);
	return (0);
}

char	check_pos(char **map)
{
	int		i;
	int		j;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ')
			{
				c = map[i][j];
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1 || (c != 'N' && c != 'S' && c != 'W' && c != 'E'))
		return (0);
	return (c);
}

int	check_error(int ac, char **av, char *file, t_data *data)
{
	char	*strfd;
	int		len;
	int		fd;

	if (ac != 2 || !av)
		return (write(2, "Error\nInvalid arguments\n", 24), -1);
	len = ft_strlen(file);
	if (len < 5 || file[len - 1] != 'b' || file[len - 2] != 'u'
		|| file[len - 3] != 'c' || file[len - 4] != '.')
		return (write(2, "Error\nFile is not a .cub\n", 26), -1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (close(fd), write(2, "Error\n", 6), perror(NULL), -1);
	strfd = init_strfd(fd);
	if (!strfd)
	{
		write(2, "Error\nAn unexpected error has occurred\n", 39);
		return (free(strfd), close(fd), -1);
	}
	if (init_data(strfd, data))
		return (close(fd), -1);
	return (close(fd), 0);
}
