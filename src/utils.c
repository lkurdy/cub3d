/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:12:13 by rben-tkh          #+#    #+#             */
/*   Updated: 2023/01/04 17:46:31 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	press(int keycode, t_data *img)
{
	img->key = 0;
	img->key = keycode;
	return (0);
}

int	release(int keycode, t_data *img)
{
	(void)keycode;
	img->key = 0;
	return (0);
}

void	get_on_the_floor(t_data *img)
{
	int	i;

	i = 0;
	while (i < (img->length * img->height) / 2)
	{
		img->pic->buf[i] = img->c_color[0] << 16;
		img->pic->buf[i] += img->c_color[1] << 8;
		img->pic->buf[i] += img->c_color[2];
		i++;
	}
	while (i < img->length * img->height)
	{
		img->pic->buf[i] = img->f_color[0] << 16;
		img->pic->buf[i] += img->f_color[1] << 8;
		img->pic->buf[i] += img->f_color[2];
		i++;
	}
}

int	get_pathlen(char *str, int *i, char pos)
{
	int	len;

	len = 0;
	while (str[*i] && str[*i] != '\n' && str[*i] != ' ' && str[*i] != '\t')
		*i += 1;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		*i += 1;
	*i += 1;
	while (str[*i] && str[*i] != '\n')
	{
		if (pos != 'F' && pos != 'C' && (str[*i] == ' ' || str[*i] == '\t'))
			break ;
		len++;
		*i += 1;
	}
	return (len);
}

char	*get_path(char *str, int *i, int j, char pos)
{
	char	*path;

	path = malloc(sizeof(char) * (j + 2));
	if (!path)
		return (0);
	*i -= j + 1;
	j = 0;
	while (str[*i] && str[*i] != '\n')
	{
		if (pos != 'F' && pos != 'C' && (str[*i] == ' ' || str[*i] == '\t'))
			break ;
		path[j++] = str[*i];
		*i += 1;
	}
	path[j] = '\0';
	j = 0;
	while (str[*i] && (str[*i] == '\n' || str[*i] == ' ' || str[*i] == '\t'))
	{
		if (str[*i] == '\n')
			j++;
		*i += 1;
	}
	if (!j)
		return (free(path), NULL);
	return (path);
}
