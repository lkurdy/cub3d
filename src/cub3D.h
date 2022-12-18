/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 06:57:31 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/12/12 06:57:33 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include "../mlx/mlx.h"

typedef struct	s_pic
{
	int	width;
	int	height;
	void	*mlx;
	void	*win;
	void	*img;
	int	*buf;
}	t_pic;

/*-----------------------------------S_DATA----------------------------------*/

typedef struct s_data
{
	t_pic	*pic;
	void	*mlx;
	void	*win;
	double		X;
	double		Y;
	double		dirX;
	double		dirY;
	double		planX;
	double		planY;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	double		cameraX;
	double		rayX;
	double		rayY;
	double		deltaX;
	double		deltaY;
	double		sideX;
	double		sideY;
	double		wall;
	int		side;
	char	**map;
	int		length;
	int		height;
	t_pic	*north;
	t_pic	*east;
	t_pic	*west;
	t_pic	*south;
	int	key;
	char	pos;
	char	*NO_path;
	char	*SO_path;
	char	*WE_path;
	char	*EA_path;
	int		*F_color;
	int		*C_color;
}	t_data;

t_pic	*new_pic(t_data *img, int width, int height, int x);
int		get_color(t_data *img, float start, int line);
void	walk_check(t_data *img, double sumY, double sumX);
void	key(int keycode, t_data *img);
void	ft_free(char **s);

/*---------------------------------INIT_DATA---------------------------------*/

char	*init_strfd(int fd);
int		init_data(char *strfd, t_data *data, char *info, int i);

/*----------------------------------PARSING----------------------------------*/

int		check_id(char *str, int i, char c);
int		check_map(char *map, char *pos, int i, int count);
int		check_error(int ac, char **av, t_data *data);

/*---------------------------------FT_SPLIT----------------------------------*/

char	**ft_split(char *s, char c);
void	ft_free(char **s);

/*-----------------------------------LIBFT-----------------------------------*/

int		ft_strlen(char *str);
char	*ft_strdup(char *str);
int		ft_atoi(char *str, int *i, int val);
char	*ft_strjoin(char *s1, char *s2);
int		ft_open(t_data *data);

/*------------------------------------T^T------------------------------------*/

#endif
