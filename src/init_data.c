/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 07:19:14 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/12/12 07:19:14 by rben-tkh         ###   ########.fr       */
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
		return (0);
	i = 1;
	while (i > 0)
	{
		i = read(fd, buffer, 42);
		if (i == -1)
		{
			free(buffer);
			return (0);
		}
		buffer[i] = '\0';
		strfd = ft_strjoin(strfd, buffer);
	}
	return (free(buffer), strfd);
}

int		*init_color(char *str)
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
	i += 1;
	color[1] = ft_atoi(str, &i, 1);
	if (color[1] == -1)
		return (free(str), free(color), NULL);
	i += 1;
	color[2] = ft_atoi(str, &i, 0);
	if (color[2] == -1)
		return (free(str), free(color), NULL);
	return (free(str), color);
}

char	*init_path(char *str, int j)
{
	char		*path;
	static int	i;
	char		c;

	while (str[i] && (str[i] == '\n' || str[i] == ' ' || str[i] == '\t'))
		i++;
	c = str[i];
	if (check_id(str, (i + 1), c))
		return (0);
	while (str[i] && str[i] != '\n' && str[i] != ' ' && str[i] != '\t')
		i++;
	while (str[i] && (str[i] == '\n' || str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[++i] && str[i] != '\n' && str[i] != ' ' && str[i] != '\t')
		j++;
	path = malloc(sizeof(char) * (j + 3));
	if (!path)
		return (0);
	i -= j + 1;
	j = 0;
	while (str[i] && str[i] != '\n' && str[i] != ' ' && str[i] != '\t')
		path[j++] = str[i++];
	path[j++] = c;
	path[j] = '\0';
	return (path);
}

char	*init_map(char *str, char **data)
{
	char	*map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	(void)data;
	while (str[i] && j != 12)
	{
		while (str[i] && (str[i] == '\n' || str[i] == ' ' || str[i] == '\t'))
			i++;
		while (str[i] && str[i] != '\n' && str[i] != ' ' && str[i] != '\t')
			i++;
		j++;
	}
	map = malloc(sizeof(char) * (ft_strlen(str) - i + 2));
	if (!map)
		return (0);
	j = 0;
	while (str[i])
		map[j++] = str[i++];
	map[j++] = '\n';
	map[j] = '\0';
	data = ft_split(ft_strdup(map), '\n');
	return (map);
}

int	init_data(char *strfd, t_data *data)
{
	char	*info;
	int		i;

	i = 6;
	while (i--)
	{
		info = init_path(strfd, 0);
		if (info && info[ft_strlen(info) - 1] == 'N')
			data->NO_path = ft_strdup(info);
		else if (info && info[ft_strlen(info) - 1] == 'S')
			data->SO_path = ft_strdup(info);
		else if (info && info[ft_strlen(info) - 1] == 'W')
			data->WE_path = ft_strdup(info);
		else if (info && info[ft_strlen(info) - 1] == 'E')
			data->EA_path = ft_strdup(info);
		else if (info && info[ft_strlen(info) - 1] == 'F')
			data->F_color = init_color(ft_strdup(info));
		else if (info && info[ft_strlen(info) - 1] == 'C')
			data->C_color = init_color(ft_strdup(info));
		else
			return (write(2, "Error\nInvalid data\n", 19), free(info), free(strfd), -1);
		free(info);
	}
	if (!data->NO_path || !data->SO_path || !data->WE_path || !data->EA_path
		|| !data->F_color || !data->C_color)
		return (write(2, "Error\nInvalid data\n", 19), free(strfd), -1);
	if (check_pos(init_map(strfd, data->map), data->pos, 0, 0))
		return (write(2, "Error\nInvalid map\n", 19), free(strfd), -1);
	return (free(strfd), 0);
}
