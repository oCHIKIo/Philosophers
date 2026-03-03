/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:42:49 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/16 22:42:50 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	post_eat_actions(t_philo *philo)
{
	int	should_stop;

	pthread_mutex_lock(&philo->data->data_mutex);
	should_stop = philo->data->simulation_stop;
	pthread_mutex_unlock(&philo->data->data_mutex);
	if (should_stop)
		return (1);
	print_action(philo, "is sleeping");
	sleep_precise(philo->data->time_to_sleep);
	pthread_mutex_lock(&philo->data->data_mutex);
	should_stop = philo->data->simulation_stop;
	pthread_mutex_unlock(&philo->data->data_mutex);
	if (should_stop)
		return (1);
	print_action(philo, "is thinking");
	if (philo->data->philo_count % 2 == 1)
		usleep(500);
	else
		usleep(100);
	return (0);
}

static int	routine_loop(t_philo *philo)
{
	int	should_stop;

	while (1)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		should_stop = philo->data->simulation_stop;
		pthread_mutex_unlock(&philo->data->data_mutex);
		if (should_stop)
			return (1);
		if (!acquire_forks(philo))
			continue ;
		pthread_mutex_lock(&philo->data->data_mutex);
		should_stop = philo->data->simulation_stop;
		pthread_mutex_unlock(&philo->data->data_mutex);
		if (should_stop)
		{
			release_forks(philo);
			return (1);
		}
		eat_meal(philo);
		release_forks(philo);
		if (post_eat_actions(philo))
			return (1);
	}
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
	{
		handle_single_philosopher(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	else if (philo->data->philo_count % 2 == 1
		&& philo->id == philo->data->philo_count - 1)
		usleep(2000);
	else
		usleep(100);
	routine_loop(philo);
	return (NULL);
}
