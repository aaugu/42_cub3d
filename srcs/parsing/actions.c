/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:26:29 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/18 09:48:41 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "../../includes/parsing.h"
#include "../../libft/include/libft.h"

void	get_rgb(t_state_machine *fsm, int *element, int i, char *color);
int		check_no_arg(t_state_machine *fsm, int i);
int		check_several_args(t_state_machine *fsm, int i);

void	set_texture(t_state_machine *fsm, char **element)
{
	int		i;
	int		j;

	if (*element)
		return (fsm_error(fsm, error, fsm->line, ERR_INFO_DUP));
	i = check_no_arg(fsm, 2);
	if (i == -1)
		return ;
	j = i;
	while (fsm->line[i] != ' ' && fsm->line[i] != '\n' && fsm->line[i])
		i++;
	*element = ft_substr(fsm->line, j, i - j);
	if (!*element)
		return (fsm_error(fsm, malloc_err, NULL, strerror(errno)));
	if (check_several_args(fsm, i) == ERROR)
		return ;
	fsm->info_count++;
}

void	set_color(t_state_machine *fsm, int *element)
{
	int		i;
	char	*color;

	if (element[0] != -1 && element[1] != -1 && element[2] != -1)
		return (fsm_error(fsm, error, fsm->line, ERR_INFO_DUP));
	i = check_no_arg(fsm, 2);
	if (i == -1)
		return ;
	color = (char *)malloc(sizeof(char) * ft_strlen(fsm->line));
	if (!color)
		return (fsm_error(fsm, malloc_err, NULL, strerror(errno)));
	get_rgb(fsm, element, i, color);
	free(color);
	i = 0;
	while (i < 3)
	{
		if (element[i] < 0 || element[i] > 255)
			return (fsm_error(fsm, error, fsm->line, ERR_ARG));
		i++;
	}
	if (check_several_args(fsm, i) == ERROR)
		return ;
	fsm->info_count++;
}

void	get_rgb(t_state_machine *fsm, int *element, int i, char *color)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while ((fsm->line[i] != ' ' && fsm->line[i] != '\n') || k > 2)
	{
		printf("caractere en cours : %c\n", fsm->line[i]);
		while (fsm->line[i] != ',')
		{
			if (fsm->line[i] >= '0' || fsm->line[i] <= '9')
			{
				color[j] = fsm->line[i];
				j++;
			}
			else
				return (fsm_error(fsm, error, fsm->line, ERR_NOT_NUM));
			i++;
		}
		color[j] = '\0';
		element[k] = ft_atoi(color);
		i++;
		j = 0;
		k++;
	}
}

int	check_no_arg(t_state_machine *fsm, int i)
{
	fsm->state = information;
	while (fsm->line[i] == ' ')
		i++;
	if (fsm->line[i] == '\n')
	{
		fsm_error(fsm, error, fsm->line, ERR_NO_ARG);
		return (-1);
	}
	return (i);
}

int	check_several_args(t_state_machine *fsm, int i)
{
	while (fsm->line[i] == ' ' && fsm->line[i] != '\n')
		i++;
	if (fsm->line[i] != '\n')
	{
		fsm_error(fsm, error, fsm->line, ERR_SEVERAL_ARGS);
		return (ERROR);
	}
	return (EXIT_SUCCESS);
}
