/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:43:09 by bchiki            #+#    #+#             */
/*   Updated: 2026/03/03 20:52:00 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_resources(t_data *data)
{
	int	i;

	i = 0;
	usleep(1000);
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->fork_mutexes[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->data_mutex);
	free(data->fork_mutexes);
	free(data->philosophers);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;

	print_banner();
	if (validate_and_init(&data, argc, argv))
		return (1);
	print_header(&data);
	create_threads(&data);
	pthread_create(&monitor, NULL, death_monitor_routine, &data);
	wait_threads(&data);
	pthread_join(monitor, NULL);
	data.sim_end_time = get_time_ms();
	print_stats(&data);
	print_footer();
	cleanup_resources(&data);
	return (0);
}
