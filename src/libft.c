/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:04:11 by rben-tkh          #+#    #+#             */
/*   Updated: 2023/01/04 18:04:21 by rben-tkh         ###   ########.fr       */
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

int	ft_atoi(char *str, int *i, int val)
{
	int		nb;
	int		count;

	nb = 0;
	count = 0;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		*i += 1;
	if (!str[*i] || !(str[*i] >= '0' && str[*i] <= '9'))
		return (-1);
	while (str[*i] && str[*i] == '0')
		*i += 1;
	while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
	{
		nb = nb * 10 + (str[*i] - '0');
		*i += 1;
		count++;
	}
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		*i += 1;
	if (nb > 255 || count > 3 || (str[*i] && val == 0)
		|| (str[*i] && str[*i] != ',' && val == 1))
		return (-1);
	if (str[*i] && str[*i + 1])
		*i += 1;
	return (nb);
}

char	*ft_strdup(char *str)
{
	char	*cpy;
	int		i;

	if (!str)
		return (0);
	i = 0;
	cpy = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!cpy)
		return (0);
	while (str[i])
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
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

int	ft_close(t_data *img)
{
	if (img->mlx)
	{
		mlx_destroy_image(img->mlx, img->north->img);
		mlx_destroy_image(img->mlx, img->east->img);
		mlx_destroy_image(img->mlx, img->west->img);
		mlx_destroy_image(img->mlx, img->south->img);
		mlx_destroy_window(img->mlx, img->win);
		mlx_destroy_display(img->mlx);
		free(img->mlx);
		free(img->north);
		free(img->east);
		free(img->west);
		free(img->south);
	}
	free(img->no_path);
	free(img->so_path);
	free(img->we_path);
	free(img->ea_path);
	free(img->f_color);
	free(img->c_color);
	ft_free(img->map);
	exit (img->ecode);
}
