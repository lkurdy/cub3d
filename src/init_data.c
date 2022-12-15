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

char	*init_path(char *strfd, int *i)
{
	char	*str;
	int		j;

	j = 0;
	while (strfd[*i] && (strfd[*i] != '\n' || strfd[*i] != ' ' || strfd[*i] != '\t'))
	{
		j++;
		*i += 1;
	}
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (0);
	*i -= j;
	j = 0;
	while (strfd[*i] && (strfd[*i] != '\n' || strfd[*i] != ' ' || strfd[*i] != '\t'))
	{
		str[j++] = strfd[*i];
		*i += 1;
	}
	str[j] = '\0';
	return (str);
}

char	*init_utils(char *strfd, char *id)
{
	char		*path;

	while (strfd[i] && (strfd[i] == '\n' || strfd[i] == ' ' || strfd[i] == '\t'))
		i++;
	if ((strfd[i] && strfd[i] != id[0]) || (strfd[i + 1] && strfd[i + 1] != id[1]))
		return (write(2, "Error\nInvalid data ID\n", 22), NULL);
	j += 2;
	while (strfd[i] && (strfd[i] != '\n' || strfd[i] != ' ' || strfd[i] != '\t'))
		i++;
	while (strfd[i] && (strfd[i] == '\n' || strfd[i] == ' ' || strfd[i] == '\t'))
		i++;
	path = init_path(strfd, &i);
	if (!path)
	{
		write(2, "Error\nAn unexpected error has occurred\n", 39);
		return (NULL);
	}
	return (path);
}

int	init_data(int fd, t_data *data)
{
	char	*strfd;
	int		i;

	strfd = init_strfd(fd);
	if (!strfd)
	{
		write(2, "Error\nAn unexpected error has occurred\n", 39);
		return (free(strfd), -1);
	}
	i = 0;
	data->NO_path = init_utils(strfd, "NO");
	data->SO_path = init_utils(strfd, "SO");
	data->WE_path = init_utils(strfd, "WE");
	data->EA_path = init_utils(strfd, "EA");
	// data->F_color = f(init_utils(strfd, data), data);
	// data->C_color = f(init_utils(strfd, data), data);
	if (!data->NO_path || !data->SO_path || !data->WE_path || !data->EA_path)
		return (free(strfd), -1);
	printf("%s\n", data->NO_path);
	printf("%s\n", data->SO_path);
	printf("%s\n", data->WE_path);
	printf("%s\n", data->EA_path);
	return (free(strfd), 0);
}
