/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:20:42 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/19 15:11:17 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing_map.h"

int	parsing_error(t_map *map, char *arg, char *str, int exit_code)
{
	if (str)
		parsing_msg(arg, str);
	parsing_map_free(map);
	return (exit_code);
}

int	parsing_msg(char *arg, char *str)
{
	printf("Error\n");
	if (arg)
		printf("%s: %s\n", arg, str);
	else
		printf("%s\n", str);
}
