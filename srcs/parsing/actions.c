/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:26:29 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/12 14:07:04 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "parsing.h"
#include "libft.h"

void	fsm_error(t_state *current_state, t_state state, char *arg, char *str)
{
	if (str)
		msg(arg, str, EXIT_FAILURE);
	current_state = state;
}

void	set_texture(t_state_machine *fsm, char **element)
{
	int		i;
	int		j;

	fsm->state = information;
	i = 0;
	while (fsm->line[i] != ' ')
		i++;
	while (fsm->line[i] == ' ')
		i++;
	if (fsm->line[i] == '\n')
		return (fsm_error(fsm->state, error, fsm->line[i], ERR_NO_ARG));
	j = i;
	i = 0;
	while (fsm->line[i] != ' ' || fsm->line[i] != '\n')
		i++;
	if (!*element)
		*element = ft_substr(fsm->line, j, i);
	else
		return (fsm_error(fsm->state, error, fsm->line[i], ERR_DUPLICATE));
	fsm->info_count++;
	if (!*element)
		return (fsm_error(fsm->state, malloc_err, NULL, strerror(errno)));
}

void	set_color(t_state *state, char *line, char **element)
{
}
