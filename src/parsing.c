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

static void	check_exit_utils(char **tab, int i, int j, int *exit)
{
	if (i < 0 || j < 0 || !tab[i] || (tab[i] && !tab[i][j])
		|| (tab[i] && tab[i][j] == ' '))
	{
		*exit = 1;
		return;
	}
	else if (tab[i][j] != '0')
		return;
	tab[i][j] = 'X';
	check_exit_utils(tab, i - 1, j, exit);
	check_exit_utils(tab, i + 1, j, exit);
	check_exit_utils(tab, i, j - 1, exit);
	check_exit_utils(tab, i, j + 1, exit);
}

static int	check_exit(char **map)
{
	int	i;
	int	j;
	int	exit;

	i = -1;
	exit = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ')
			{
				map[i][j] = '0';
				check_exit_utils(map, i, j, &exit);
				if (exit == 1)
					return (-1);
			}
		}
	}
	return (0);
}

int	check_map(char *map, char *pos, int i, int count)
{
	while (map[i] && (map[i] == '\n' || map[i] == ' ' || map[i] == '\t'))
		i++;
	while (i > 0 && map[i - 1] && map[i - 1] != '\n')
		i--;
	while (map[i])
	{
		if (map[i + 1] && map[i] == '\n' && (map[i + 1] == '\n' || map[i + 1] == '\t'))
			break ;
		if ((map[i] != '0' && map[i] != '1' && map[i] != ' ' && map[i] != '\n'))
		{
			*pos = map[i];
			count++;
		}
		i++;
	}
	if (count != 1 || (*pos != 'N' && *pos != 'S' && *pos != 'W' && *pos != 'E'))
		return (free(map), -1);
	while (map[i] && (map[i] == '\n' || map[i] == ' ' || map[i] == '\t'))
		i++;
	if (map[i])
		return (free(map), -1);
	return (check_exit(ft_split(map, '\n')));
}

int	check_error(int ac, char **av, t_data *data)
{
	char	*strfd;
	int		len;
	int		fd;

	if (ac != 2 || !av)
		return (write(2, "Error\nInvalid arguments\n", 24), -1);
	len = ft_strlen(av[1]);
	if (len < 5 || av[1][len - 1] != 'b' || av[1][len - 2] != 'u'
		|| av[1][len - 3] != 'c' || av[1][len - 4] != '.')
		return (write(2, "Error\nFile is not a .cub\n", 26), -1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (close(fd), write(2, "Error\n", 6), perror(av[1]), -1);
	strfd = init_strfd(fd);
	if (!strfd)
	{
		write(2, "Error\n", 6);
		return (perror(av[1]), free(strfd), close(fd), -1);
	}
	if (init_data(strfd, data, 0, 6))
		return (close(fd), -1);
	if (ft_open(data))
		return (close(fd), -1);
	return (close(fd), 0);
}
