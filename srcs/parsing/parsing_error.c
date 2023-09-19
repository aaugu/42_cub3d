/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:20:42 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/19 13:07:48 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing_map.h"

int	parsing_error(char *arg, char *str, int exit_code)
{
	printf("Error\n");
	if (arg)
		printf("%s: %s\n", arg, str);
	else
		printf("%s\n", str);
	return (exit_code);
}
