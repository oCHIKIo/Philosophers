/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:42:22 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/16 23:04:47 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static const char	*get_color(int id)
{
	static const char	*colors[6] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN};

	return (colors[id % 6]);
}

static const char	*get_icon(const char *action)
{
	if (action[0] == 'h')
		return ("🍴");
	if (action[0] == 'i' && action[3] == 'e')
		return ("🍽️");
	if (action[0] == 'i' && action[3] == 's')
		return ("😴");
	if (action[0] == 'i' && action[3] == 't')
		return ("🤔");
	if (action[0] == 'd')
		return ("💀");
	return ("❓");
}

void	print_action(t_philo *philo, const char *action)
{
	int	should_print;

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->data_mutex);
	should_print = !philo->data->simulation_stop || action[0] == 'd';
	pthread_mutex_unlock(&philo->data->data_mutex);
	if (should_print)
	{
		printf("%s%s%lld%s %s%s%d%s %s%s %s%s%s\n", DIM, WHITE, get_time_ms()
			- philo->data->sim_start_time, RESET, get_color(philo->id), BOLD,
			philo->id + 1, RESET, get_icon(action), get_color(philo->id),
			action, RESET, RESET);
		if (action[0] == 'd')
		{
			pthread_mutex_lock(&philo->data->data_mutex);
			philo->data->simulation_stop = 1;
			philo->data->death_occurred = 1;
			pthread_mutex_unlock(&philo->data->data_mutex);
			printf("%s%s💀 PHILOSOPHER %d HAS DIED! 💀%s\n", BOLD, BG_RED,
				philo->id + 1, RESET);
		}
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	print_stats(t_data *data)
{
	printf("\n%s%s", BOLD, GREEN);
	printf("┌─────────────────── SIMULATION STATISTICS ───────────────────┐\n");
	printf(" 🍽️  Total meals served: %s%lld%s%s                          \n",
		YELLOW, data->total_meals, GREEN, BOLD);
	printf(" ⚰️  Deaths: %s%d%s%s                                        \n",
		RED, data->death_occurred, GREEN, BOLD);
	if (data->must_eat_count > 0)
		printf(" ✅ Philosophers satisf"
			"ied: %s%lld/%d%s%s                     \n",
			CYAN, data->satisfied_count, data->philo_count, GREEN, BOLD);
	if (data->death_occurred == 0 && (data->must_eat_count < 0
			|| data->satisfied_count == data->philo_count))
		printf("│ 🏆 %sSIMULATION COMPLETED "
			"SUCCESSFULLY!%s%s%s                       │\n",
			BG_GREEN, RESET, GREEN, BOLD);
	else if (data->death_occurred > 0)
		printf("│ 💀 %sSIMULATION ENDED DUE TO "
			"DEATH%s%s%s                            │\n",
			BG_RED, RESET, GREEN, BOLD);
	printf("└──────────────────────────"
		"───────────────────────────────────┘%s\n", RESET);
}
