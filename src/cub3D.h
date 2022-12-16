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

/*-----------------------------------S_DATA----------------------------------*/

typedef struct s_data
{
	char	*NO_path;
	char	*SO_path;
	char	*WE_path;
	char	*EA_path;
	int		*F_color;
	int		*C_color;
	char	**map;
	char	pos;
}	t_data;

/*---------------------------------INIT_DATA---------------------------------*/

char	*init_strfd(int fd);
int		init_data(char *strfd, t_data *data);

/*----------------------------------PARSING----------------------------------*/

int		check_id(char *str, int i, char c);
char	check_pos(char **map);
int		check_error(int ac, char **av, char *file, t_data *data);

/*-----------------------------------LIBFT-----------------------------------*/

int		ft_strlen(char *str);
char	*ft_strdup(char *str);
int		ft_atoi(char *str, int *i, int val);
char	*ft_strjoin(char *s1, char *s2);

/*---------------------------------FT_SPLIT----------------------------------*/

char	**ft_split(char *s, char c);
char	**ft_free(char **dest, int j);

/*------------------------------------T^T------------------------------------*/

#endif
