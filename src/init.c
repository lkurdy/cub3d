/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 07:19:14 by rben-tkh          #+#    #+#             */
/*   Updated: 2023/01/04 17:37:02 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*init_strfd(int fd)
{
	char	*strfd;
	char	*buffer;
	int		i;

	strfd = malloc(sizeof(char));
	if (!strfd)
		return (0);
	strfd[0] = '\0';
	buffer = malloc(sizeof(char) * (42 + 1));
	if (!buffer)
		return (free(strfd), NULL);
	i = 1;
	while (i > 0)
	{
		i = read(fd, buffer, 42);
		if (i == -1)
			return (free(strfd), free(buffer), NULL);
		buffer[i] = '\0';
		strfd = ft_strjoin(strfd, buffer);
	}
	return (free(buffer), strfd);
}

int	*init_color(char *str)
{
	int	*color;
	int	i;

	if (!str)
		return (free(str), NULL);
	color = malloc(sizeof(int) * 3);
	if (!color)
		return (0);
	i = 0;
	color[0] = ft_atoi(str, &i, 1);
	if (color[0] == -1)
		return (free(str), free(color), NULL);
	color[1] = ft_atoi(str, &i, 1);
	if (color[1] == -1)
		return (free(str), free(color), NULL);
	color[2] = ft_atoi(str, &i, 0);
	if (color[2] == -1)
		return (free(str), free(color), NULL);
	return (free(str), color);
}

char	*init_path(char *str, char *pos, int j, int *checker)
{
	static int	i;

	while (str[i] && (str[i] == '\n' || str[i] == ' ' || str[i] == '\t'))
		i++;
	while (!*checker && str[i++])
	{
		if (!*checker && str[i] != '1' && str[i] != '0'
			&& str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			j++;
	}
	if (!*checker && j != 2)
		return (*checker = -42, NULL);
	else if (!*checker)
		return (0);
	j = 0;
	*pos = str[i];
	if (check_id(str, (i + 1), *pos))
		return (0);
	return (get_path(str, &i, get_pathlen(str, &i, *pos), *pos));
}

char	*init_map(char *str, char ***data, int i, int j)
{
	char	*map;

	while (str[i] && str[i + 1])
		i++;
	while (str[i] != 'N' && str[i] != 'S' && str[i] != 'W'
		&& str[i] != 'E' && str[i] != 'F' && str[i] != 'C')
		i--;
	while (str[i - 1] != 'N' && str[i - 1] != 'S' && str[i - 1] != 'W'
		&& str[i - 1] != 'E' && str[i - 1] != 'F' && str[i - 1] != 'C')
		i--;
	while (str[i] && str[i] != '\n')
		i++;
	while (str[++i])
		j++;
	map = malloc(sizeof(char) * (j + 1));
	if (!map)
		return (0);
	i -= j;
	j = 0;
	while (str[i])
		map[j++] = str[i++];
	return (map[j] = '\0', *data = ft_split(map, '\n'), map);
}

void	init_pos(t_data *img)
{
	img->dir_x = 0;
	img->dir_y = -1;
	img->planx = 0.66;
	img->plany = 0;
	if (img->pos == 'E')
	{
		img->dir_x = 1;
		img->dir_y = 0;
		img->planx = 0;
		img->plany = 0.66;
	}
	else if (img->pos == 'W')
	{
		img->dir_x = -1;
		img->dir_y = 0;
		img->planx = 0;
		img->plany = -0.66;
	}
	else if (img->pos == 'S')
	{
		img->dir_x = 0;
		img->dir_y = 1;
		img->planx = -0.66;
		img->plany = 0;
	}
}
