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

static int	*init_color(char *str)
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

static char	*init_path(char *str, char *pos, int j, int *checker)
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

static char	*init_map(char *str, char ***data, int i, int j)
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

int	init_data(char *strfd, t_data *data, char *info, int i)
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
