/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:54:22 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/12/26 20:43:00 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	size(const char *str, char set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (((str[i] != set) && (str[i + 1] == set))
			|| ((str[i] != set) && !str[i + 1]))
			j++;
		i++;
	}
	return (j);
}

static char	*ft_cpy(char *dest, const char *str, int n)
{
	int	i;

	i = 0;
	while (str[i] && i < n)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**remp(int *i, int *j, const char *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = malloc(sizeof(const char *) * (size(s, c) + 1));
	*i = 0;
	*j = 0;
	return (dest);
}

char	**ft_split(char *s, char c)
{
	char	**dest;
	int		i;
	int		j;
	int		g;

	dest = remp(&i, &j, s, c);
	if (!dest)
		return (NULL);
	while (j < size(s, c) && s[i])
	{
		g = i;
		while ((s[i] != c) && s[i])
			i++;
		if (i)
		{
			dest[j] = malloc(sizeof(const char) * (i - g + 1));
			if (!dest[j])
				return (ft_free(dest), NULL);
			dest[j] = ft_cpy(dest[j], &s[g], i - g);
			j++;
		}
		while ((s[i] == c) && s[i])
			i++;
	}
	return (dest[j] = 0, dest);
}

void	ft_free(char **s)
{
	int	i;
	int	j;

	if (!s)
		return ;
	i = 0;
	j = 0;
	while (s[i])
		i++;
	while (j < i)
	{
		free(s[j]);
		j++;
	}
	free(s[j]);
	free(s);
}
