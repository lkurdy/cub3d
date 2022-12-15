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

static char	*init_strfd(int fd)
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

char	*init_path(char *str, char f, char s, int j)
{
	char		*path;
	static int	i;

	while (str[i] && (str[i] == '\n' || str[i] == ' ' || str[i] == '\t'))
		i++;
	if ((str[i] && str[i] != f) || (s && str[i + 1] && str[i + 1] != s)
		|| (s && str[i + 2] && str[i + 2] != ' ' && str[i + 2] != '\t')
		|| (!s && str[i + 1] != ' ' && str[i + 1] != '\t'))
		return (0);
	while (str[i] && str[i] != '\n' && str[i] != ' ' && str[i] != '\t')
		i++;
	while (str[i] && (str[i] == '\n' || str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[++i] && str[i] != '\n' && str[i] != ' ' && str[i] != '\t')
		j++;
	path = malloc(sizeof(char) * (j + 2));
	if (!path)
		return (0);
	i -= j + 1;
	j = 0;
	while (str[i] && str[i] != '\n' && str[i] != ' ' && str[i] != '\t')
		path[j++] = str[i++];
	path[j] = '\0';
	return (path);
}

int	init_data(int fd, t_data *data)
{
	char	*strfd;

	strfd = init_strfd(fd);
	if (!strfd)
	{
		write(2, "Error\nAn unexpected error has occurred\n", 39);
		return (free(strfd), -1);
	}
	data->NO_path = init_path(strfd, 'N', 'O', 0);
	data->SO_path = init_path(strfd, 'S', 'O', 0);
	data->WE_path = init_path(strfd, 'W', 'E', 0);
	data->EA_path = init_path(strfd, 'E', 'A', 0);
	data->F_color = init_color(init_path(strfd, 'F', 0, 0));
	data->C_color = init_color(init_path(strfd, 'C', 0, 0));
	if (!data->NO_path || !data->SO_path || !data->WE_path || !data->EA_path
		|| !data->F_color || !data->C_color)
		return (write(2, "Error\nInvalid data\n", 19), free(strfd), -1);
	printf("%s\n", data->NO_path);
	printf("%s\n", data->SO_path);
	printf("%s\n", data->WE_path);
	printf("%s\n", data->EA_path);
	printf("%d,%d,%d\n", data->F_color[0], data->F_color[1], data->F_color[2]);
	printf("%d,%d,%d\n", data->C_color[0], data->C_color[1], data->C_color[2]);
	return (free(strfd), 0);
}
