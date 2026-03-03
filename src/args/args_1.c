/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:39:42 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/17 12:12:49 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	init_simulation_data(t_data *data, int argc, char **argv)
{
	data->philo_count = safe_atoi(argv[1]);
	data->time_to_die = safe_atoi(argv[2]);
	data->time_to_eat = safe_atoi(argv[3]);
	data->time_to_sleep = safe_atoi(argv[4]);
	data->must_eat_count = -1;
	if (argc == 6)
		data->must_eat_count = safe_atoi(argv[5]);
	if (data->philo_count < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1 || (argc == 6 && data->must_eat_count < 1))
		return (1);
	data->sim_start_time = get_time_ms();
	data->sim_end_time = 0;
	data->total_meals = 0;
	data->satisfied_count = 0;
	data->simulation_stop = 0;
	data->death_occurred = 0;
	return (0);
}

static int	allocate_memory(t_data *data)
{
	int	i;

	data->fork_mutexes = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	data->philosophers = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->fork_mutexes || !data->philosophers)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->fork_mutexes[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->data_mutex, NULL);
	return (0);
}

static void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].left_fork = i;
		data->philosophers[i].right_fork = (i + 1) % data->philo_count;
		data->philosophers[i].last_meal_time = data->sim_start_time;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].satisfied = 0;
		data->philosophers[i].has_forks = 0;
		data->philosophers[i].data = data;
		i++;
	}
}

int	validate_and_init(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("%s%sError: invalid arguments%s\n", BOLD, RED, RESET);
		return (1);
	}
	if (init_simulation_data(data, argc, argv))
	{
		printf("%s%sError: invalid numeric values%s\n", BOLD, RED, RESET);
		return (1);
	}
	if (allocate_memory(data))
	{
		printf("%s%sError: allocation failed%s\n", BOLD, RED, RESET);
		return (1);
	}
	init_philosophers(data);
	return (0);
}
