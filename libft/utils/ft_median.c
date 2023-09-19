/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_median.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:53:28 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/19 09:39:12 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_median(int *list, int size)
{
	int	median;

	ft_sort(list, size);
	if (size % 2 == 0)
		median = list[(size / 2) - 1];
	else
		median = list[size / 2];
	return (median);
	return (0);
}

// int	ft_median_strs(char **list, int size)
// {
// 	int		i;
// 	char	*median;

// 	ft_sort_strs(list, size);
// 	if (size % 2 == 0)
// 		median = list[(size / 2) - 1];
// 	else
// 		median = list[size / 2];
// 	return (ft_atoi(median));
// }