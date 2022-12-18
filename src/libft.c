/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:04:11 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/12/12 09:04:12 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = malloc(sizeof(char) * ft_strlen(str));
	if (!cpy)
		return (0);
	while (str[i] && str[i + 1])
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

int	ft_atoi(char *str, int *i, int val)
{
	long	nb;
	int		res;
	int		count;

	nb = 0;
	res = 0;
	count = 0;
	if (!str[*i])
		return (-1);
	while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
	{
		res = res * 10 + (str[*i] - '0');
		nb = nb * 10 + (str[*i] - '0');
		*i += 1;
		count++;
	}
	if (nb != res || count > 9 || (str[*i] && val == 0)
		|| (str[*i] && str[*i] != ',' && val == 1))
		return (-1);
	return (nb);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 && !s2)
		return (0);
	else if (!s1 && s2)
		return (s2);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (free(s1), str);
}

int	ft_open(t_data *data)
{
	int	fd;
	char c;

	fd = open(data->NO_path, O_RDONLY, O_DIRECTORY);
	if (fd == -1 || read(fd, &c, 1) == -1)
		return (write(2, "Error\n", 6), perror(data->NO_path), close(fd), -1);
	close(fd);
	fd = open(data->SO_path, O_RDONLY, O_DIRECTORY);
	if (fd == -1 || read(fd, &c, 1) == -1)
		return (write(2, "Error\n", 6), perror(data->SO_path), close(fd), -1);
	close(fd);
	fd = open(data->WE_path, O_RDONLY, O_DIRECTORY);
	if (fd == -1 || read(fd, &c, 1) == -1)
		return (write(2, "Error\n", 6), perror(data->WE_path), close(fd), -1);
	close(fd);
	fd = open(data->EA_path, O_RDONLY, O_DIRECTORY);
	if (fd == -1 || read(fd, &c, 1) == -1)
		return (write(2, "Error\n", 6), perror(data->EA_path), close(fd), -1);
	return (close(fd), 0);
}
