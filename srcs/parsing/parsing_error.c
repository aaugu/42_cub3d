/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:46:10 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/11 11:47:13 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_map	parsing_error(char *str, char *arg, t_map *map)
{
	if (arg)
		printf("%s: %s", arg, str);
	else
		printf("%s", str);
	return (*map);
}
