/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:26:29 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/19 09:42:20 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "../../includes/parsing.h"
#include "../../libft/include/libft.h"

int		check_args(t_state_machine *fsm, int i, int args);
int		get_rgb(t_state_machine *fsm, int *element, int i);
bool	rgb_values_valid(int *rgb);

void	set_texture(t_state_machine *fsm, char **element)
{
	int		i;
	int		j;

	if (*element)
		return (fsm_error(fsm, error, fsm->line, ERR_INFO_DUP));
	fsm->state = information;
	i = check_args(fsm, 2, NO_ARG);
	if (i == -1)
		return ;
	j = i;
	while (fsm->line[i] != ' ' && fsm->line[i] != '\n' && fsm->line[i])
		i++;
	*element = ft_substr(fsm->line, j, i - j);
	if (!*element)
		return (fsm_error(fsm, malloc_err, NULL, strerror(errno)));
	if (check_args(fsm, i, SEVERAL_ARGS) == ERROR)
		return ;
	fsm->info_count++;
}

void	set_color(t_state_machine *fsm, int *rgb)
{
	int		i;
	int		j;

	if (rgb[0] != -1 && rgb[1] != -1 && rgb[2] != -1)
		return (fsm_error(fsm, error, fsm->line, ERR_INFO_DUP));
	fsm->state = information;
	i = check_args(fsm, 2, NO_ARG);
	if (i == -1)
		return ;
	j = get_rgb(fsm, rgb, i);
	if (!rgb_values_valid(rgb))
		return (fsm_error(fsm, error, fsm->line, ERR_ARG));
	if (check_args(fsm, j, SEVERAL_ARGS) == ERROR)
		return ;
	fsm->info_count++;
}

int	get_rgb(t_state_machine *fsm, int *rgb, int i)
{
	int	j;

	j = -1;
	while (fsm->line[i] != ' ' && fsm->line[i] && j < 3)
	{
		rgb[++j] = 0;
		while (fsm->line[i] != ',' && fsm->line[i] != ' ' && fsm->line[i]
			&& fsm->line[i] != '\n')
		{
			if (fsm->line[i] >= '0' || fsm->line[i] <= '9')
				rgb[j] = (rgb[j] * 10) + (fsm->line[i] - '0');
			else
			{
				fsm_error(fsm, error, fsm->line, ERR_NOT_NUM);
				return (ERROR);
			}
			i++;
		}
		i++;
	}
	return (i);
}

bool	rgb_values_valid(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (false);
		i++;
	}
	return (true);
}

int	check_args(t_state_machine *fsm, int i, int args)
{
	while (fsm->line[i] == ' ')
		i++;
	if ((fsm->line[i] == '\n' || fsm->line[i] == '\0') && !args)
		fsm_error(fsm, error, fsm->line, ERR_NO_ARG);
	if (fsm->line[i] != '\n' && fsm->line[i] != '\0' && args)
		fsm_error(fsm, error, fsm->line, ERR_SEVERAL_ARGS);
	return (i);
}
