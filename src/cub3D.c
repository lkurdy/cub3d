/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 06:57:16 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/12/12 06:57:19 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int ac, char **av)
{
	t_data	data;

	if (check_error(ac, av, av[1], &data))
		return (-1);
	/*-----------------------------------TEST--------------------------------*/
	printf("NO = %s\n", data.NO_path);
	printf("SO = %s\n", data.SO_path);
	printf("WE = %s\n", data.WE_path);
	printf("EA = %s\n", data.EA_path);
	printf("F = %d,%d,%d\n", data.F_color[0], data.F_color[1], data.F_color[2]);
	printf("C = %d,%d,%d\n", data.C_color[0], data.C_color[1], data.C_color[2]);
	int	i = 0;
	while (data.map[i])
		printf("%s\n", data.map[i++]);
	printf("POS = %c\n", data.pos);
	/*-----------------------------------TEST--------------------------------*/
	return (0);
}
