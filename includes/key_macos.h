/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_macos.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:13:50 by lvogt             #+#    #+#             */
/*   Updated: 2023/09/11 10:23:31 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_MACOS_H
# define KEY_MACOS_H

# define ARROW_LEFT		123
# define ARROW_RIGHT	124
# define ARROW_UP		126
# define ARROW_DOWN		125

# define MOUSE_LEFT		1
# define MOUSE_RIGHT	2
# define MOUSE_MIDDLE	3
# define MOUSE_UP		4
# define MOUSE_DOWN		5

# define MAINP_ESC		53
# define MAINP_SPACE	49
# define MAINP_PLUS		24
# define MAINP_MINUS	27
# define MAINP_W		13
# define MAINP_A		0
# define MAINP_S		1
# define MAINP_D		2
# define MAINP_R		15
# define MAINP_P		35
# define MAINP_DOT		47
# define MAINP_1		18
# define MAINP_2		19
# define MAINP_3		20
# define MAINP_4		23
# define MAINP_5		21
# define MAINP_6		22
# define MAINP_7		26
# define MAINP_8		28
# define MAINP_9		25
# define MAINP_0		29

# define NUMP_PLUS		69
# define NUMP_MINUS		78
# define NUMP_1			83
# define NUMP_2			84
# define NUMP_3			85
# define NUMP_4			87
# define NUMP_5			86
# define NUMP_6			88
# define NUMP_7			89
# define NUMP_8			91
# define NUMP_9			92
# define NUMP_0			82

# define KeyPress		02
# define KeyRelease		03
# define ButtonPress	04
# define ButtonRelease	05
# define MotionNotify	06
# define DestroyNotify	17
# define ClientMessage	33

# define NoEventMask		0L
# define KeyPressMask		1L<<0
# define KeyReleaseMask		1L<<1
# define PointerMotionMask	1L<<6

#endif
