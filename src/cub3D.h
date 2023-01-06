/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 06:57:31 by rben-tkh          #+#    #+#             */
/*   Updated: 2023/01/04 18:04:00 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include "../mlx/mlx.h"

/*-----------------------------------S_PIC-----------------------------------*/

typedef struct s_pic
{
	int		width;
	int		height;
	void	*mlx;
	void	*win;
	void	*img;
	int		*buf;
}	t_pic;

/*-----------------------------------S_DATA----------------------------------*/

typedef struct s_data
{
	t_pic	*pic;
	void	*mlx;
	void	*win;
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	planx;
	double	plany;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	camera_x;
	double	ray_x;
	double	ray_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	wall;
	int		side;
	char	**map;
	int		length;
	int		height;
	t_pic	*north;
	t_pic	*east;
	t_pic	*west;
	t_pic	*south;
	int		key;
	char	pos;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		*f_color;
	int		*c_color;
	int		ecode;
}	t_data;

/*---------------------------------INIT_DATA---------------------------------*/

char	*init_strfd(int fd);
int		init_data(char *strfd, t_data *data, char *info, int i);

/*----------------------------------PARSING----------------------------------*/

int		check_id(char *str, int i, char c);
int		check_map(char *map, char *pos, int i, int count);
int		check_texture(t_data *data, int fd, char c);

/*---------------------------------FT_SPLIT----------------------------------*/

char	**ft_split(char *s, char c);
void	ft_free(char **s);

/*-----------------------------------MATH------------------------------------*/

double	find_x(char **map, t_data *img);
double	find_y(char **map, t_data *img);
int		dda(t_data *img);
void	key(int keycode, t_data *img, double temp);

/*----------------------------------DISPLAY----------------------------------*/

t_pic	*new_pic(t_data *img, int width, int height, int x);
int		ray(void *param);

/*-----------------------------------UTILS-----------------------------------*/

void	get_pos(t_data *img);
void	get_on_the_floor(t_data *img);
int		get_pathlen(char *str, int *i, char pos);
char	*get_path(char *str, int *i, int j, char pos);

/*-----------------------------------LIBFT-----------------------------------*/

int		ft_strlen(char *str);
char	*ft_strdup(char *str);
int		ft_atoi(char *str, int *i, int val);
char	*ft_strjoin(char *s1, char *s2);
int		ft_close(t_data *img);

/*------------------------------------T^T------------------------------------*/

#endif
