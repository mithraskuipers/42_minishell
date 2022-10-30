/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splash.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 10:33:21 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 13:19:28 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "splash.h"
#include <stdio.h>
#include <unistd.h>

static void	color_green(void)
{
	printf("\033[0;32m");
}

static void	color_reset(void)
{
	printf("\033[0m");
}

static void	clear_screen(void)
{
	write(1, "\x1b[2J", 4);
	write(1, "\x1b[H", 3);
}

void	splash(void)
{
	clear_screen();
	color_green();
	printf("%s", SPLASH);
	color_reset();
}
