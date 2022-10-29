/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splash.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 10:33:21 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 10:40:30 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "splash.h"
#include <stdio.h>
#include <unistd.h>

static void	color_green()
{
	printf("\033[0;32m");
}

static void	color_reset()
{
	printf("\033[0m");
}

static void	clear_screen(void)
{
	write(1, "\x1b[2J", 4); // TODO: misschien hierdoor problemen
	write(1, "\x1b[H", 3); // en hier
}

void	splash(void)
{
	clear_screen();
	color_green();
	printf("%s", SPLASH);
	color_reset();
}