/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:42:18 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/16 22:42:19 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_all_satisfied(t_data *data)
{
	int	satisfied;

	pthread_mutex_lock(&data->data_mutex);
	satisfied = data->satisfied_count;
	pthread_mutex_unlock(&data->data_mutex);
	if (data->must_eat_count > 0 && satisfied >= data->philo_count)
	{
		pthread_mutex_lock(&data->data_mutex);
		if (!data->simulation_stop)
		{
			data->simulation_stop = 1;
			pthread_mutex_unlock(&data->data_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("%s%s🎉 ALL PHILOSOPHERS HAVE EATEN "
				"ENOUGH! SIMULATION COMPLETE! 🎉%s\n",
				BOLD, BG_GREEN, RESET);
			pthread_mutex_unlock(&data->print_mutex);
		}
		else
			pthread_mutex_unlock(&data->data_mutex);
		return (1);
	}
	return (0);
}

static int	check_philosopher_death(t_data *data, int i)
{
	long long	current_time;
	long long	last_meal;
	int			already_stopped;

	current_time = get_time_ms();
	pthread_mutex_lock(&data->data_mutex);
	last_meal = data->philosophers[i].last_meal_time;
	already_stopped = data->simulation_stop;
	pthread_mutex_unlock(&data->data_mutex);
	if (!already_stopped && current_time - last_meal > data->time_to_die)
	{
		print_action(&data->philosophers[i], "died");
		return (1);
	}
	return (0);
}

static int	scan_philosophers(t_data *data)
{
	int	i;
	int	should_stop;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->data_mutex);
		should_stop = data->simulation_stop;
		pthread_mutex_unlock(&data->data_mutex);
		if (should_stop)
			return (1);
		if (check_philosopher_death(data, i))
			return (1);
		i++;
	}
	return (0);
}

void	*death_monitor_routine(void *arg)
{
	t_data	*data;
	int		should_stop;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->data_mutex);
		should_stop = data->simulation_stop;
		pthread_mutex_unlock(&data->data_mutex);
		if (should_stop)
			break ;
		if (scan_philosophers(data))
			break ;
		pthread_mutex_lock(&data->data_mutex);
		should_stop = data->simulation_stop;
		pthread_mutex_unlock(&data->data_mutex);
		if (should_stop)
			break ;
		if (check_all_satisfied(data))
			break ;
		usleep(100);
	}
	return (NULL);
}
