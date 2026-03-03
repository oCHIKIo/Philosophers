/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:42:40 by bchiki            #+#    #+#             */
/*   Updated: 2026/03/03 21:31:23 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_banner(void)
{
	printf("%s%s", BOLD, CYAN);
	printf("╔════════════════════════════════"
		"══════════════════════════════╗\n");
	printf("║                    🍽️  PHILOSOPHERS DI"
		"NING  🍽️                 ║\n");
	printf("║                       Advanced Simul"
		"ation                    ║\n");
	printf("╚═════════════════════════════════════"
		"═════════════════════════╝%s\n", RESET);
}

void	print_header(t_data *data)
{
	printf("\n%s%s", BOLD, BLUE);
	printf("┌─────────────────── SIMULATION PA"
		"RAMETERS ───────────────────┐\n");
	printf(" 👥 Philosophers: %s%d%s%s              "
		"                     \n", CYAN, data->philo_count, BLUE, BOLD);
	printf(" ⏰ Time to die: %s%lld ms%s%s         "
		"                     \n", RED, data->time_to_die, BLUE, BOLD);
	printf(" 🍽️  Time to eat: %s%lld ms%s%s         "
		"                    \n", GREEN, data->time_to_eat, BLUE, BOLD);
	printf(" 😴 Time to sleep: %s%lld ms%s%s              "
		"              \n", MAGENTA, data->time_to_sleep, BLUE, BOLD);
	if (data->must_eat_count > 0)
		printf(" 🎯 Must eat: %s%lld times%s%s          "
			"                    \n", YELLOW, data->must_eat_count, BLUE, BOLD);
	else
		printf(" 🎯 Must eat: %sUnlimited%s%s           "
			"                    \n", YELLOW, BLUE, BOLD);
	printf("└──────────────────────────────────────────────"
		"───────────────┘%s\n", RESET);
	printf("\n%s%s📊 SIMULATION LOG:%s\n", BOLD, CYAN, RESET);
}

void	print_footer(void)
{
	printf("\n%s%s", BOLD, MAGENTA);
	printf("╔═══════════════════════════════"
		"═══════════════════════════════╗\n");
	printf("║                   🎭 SIMULATION C"
		"OMPLETE 🎭                  ║\n");
	printf("╚════════════════════════════════════"
		"══════════════════════════╝%s\n", RESET);
}
