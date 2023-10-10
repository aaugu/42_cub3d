/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:12:56 by aaugu             #+#    #+#             */
/*   Updated: 2023/10/10 14:25:51 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <colors.h>
#include <bonus.h>

void	print_logo(void);

void	print_controls(void)
{
	print_logo();
	printf(CYAN "\tW" RESET ": move forward\t");
	printf(CYAN "\tS" RESET ": move backward\n");
	printf(CYAN "\tA" RESET ": strafe left\t");
	printf(CYAN "\tD" RESET ": strafe right\n");
	printf(CYAN "\t<" RESET ": rotate left\t");
	printf(CYAN "\t>" RESET ": rotate right\n");
	if (BONUS)
	{
		printf(CYAN "\tMouse" RESET ": rotate view");
		printf(CYAN "\tM" RESET ": display on/off minimap");
		printf(CYAN "\tspace" RESET ": open/close door");
	}
	printf(CYAN "\tesc" RESET ": close cub3D\n");
	printf("\n");
}

void	print_logo(void)
{
	printf(PURPLE "\n");
	printf("                                    .--,-``-.                  \n");
	printf("  ,----..                  ,---,.  /   /     '.      ,---,     \n");
	printf(" /   /   \\         ,--,  ,'  .'  \\/ ../        ;   .'  .' `\\  ");
	printf(" \n");
	printf("|   :     :      ,'_ /|,---.' .' |\\ ``\\  .`-    ',---.'     \\ ");
	printf(" \n");
	printf(".   |  ;. / .--. |  | :|   |  |: | \\___\\/   \\   :|   |  .`\\  ");
	printf("| \n");
	printf(".   ; /--`,'_ /| :  . |:   :  :  /      \\   :   |:   : |  '  | ");
	printf("\n");
	printf(";   | ;   |  ' | |  . .:   |    ;       /  /   / |   ' '  ;  : \n");
	printf("|   : |   |  | ' |  | ||   :     \\      \\  \\   \\ '   | ;  .  ");
	printf("| \n");
	printf(".   | '___:  | | :  ' ;|   |   . |  ___ /   :   ||   | :  |  ' \n");
	printf("'   ; : .'|  ; ' |  | ''   :  '; | /   /\\   /   :'   : | /  ;  ");
	printf("\n");
	printf("'   | '/  :  | : ;  ; ||   |  | ; / ,,/  ',-    .|   | '` ,/   \n");
	printf("|   :    /'  :  `--'   \\   :   /  \\ ''\\        ; ;   :  .'    ");
	printf(" \n");
	printf(" \\   \\ .' :  ,      .-./   | ,'    \\   \\     .'  |   ,.'     ");
	printf("  \n");
	printf("  `---`    `--`----'   `----'       `--`-,,-'    '---'         \n");
	printf(RESET "\n");
}
