/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:20:42 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/12 10:03:04 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/message.h"

int	msg(char *arg, char *str, int exit_code)
{
	printf("Error\n");
	if (arg)
		printf("%s: %s", arg, str);
	else
		printf("%s", str);
	return (exit_code);
}
