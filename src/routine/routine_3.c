/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:43:01 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/16 23:07:53 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	take_second_and_check(t_philo *philo, int first_fork,
		int second_fork, int should_stop)
{
	if (should_stop)
	{
		pthread_mutex_unlock(&philo->data->fork_mutexes[first_fork]);
		return (0);
	}
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->fork_mutexes[second_fork]);
	pthread_mutex_lock(&philo->data->data_mutex);
	should_stop = philo->data->simulation_stop;
	pthread_mutex_unlock(&philo->data->data_mutex);
	if (should_stop)
	{
		pthread_mutex_unlock(&philo->data->fork_mutexes[first_fork]);
		pthread_mutex_unlock(&philo->data->fork_mutexes[second_fork]);
		return (0);
	}
	print_action(philo, "has taken a fork");
	philo->has_forks = 1;
	return (1);
}

int	acquire_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;
	int	should_stop;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(&philo->data->fork_mutexes[first_fork]);
	pthread_mutex_lock(&philo->data->data_mutex);
	should_stop = philo->data->simulation_stop;
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (take_second_and_check(philo, first_fork, second_fork, should_stop));
}

void	release_forks(t_philo *philo)
{
	if (philo->has_forks)
	{
		pthread_mutex_unlock(&philo->data->fork_mutexes[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->fork_mutexes[philo->right_fork]);
		philo->has_forks = 0;
	}
}

void	handle_single_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_mutexes[philo->left_fork]);
	philo->has_forks = 1;
	print_action(philo, "has taken a fork");
	sleep_precise(philo->data->time_to_die);
	print_action(philo, "died");
	pthread_mutex_unlock(&philo->data->fork_mutexes[philo->left_fork]);
	philo->has_forks = 0;
}

void	eat_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->data_mutex);
	print_action(philo, "is eating");
	sleep_precise(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->meals_eaten++;
	philo->data->total_meals++;
	if (philo->data->must_eat_count > 0 && !philo->satisfied
		&& philo->meals_eaten >= philo->data->must_eat_count)
	{
		philo->satisfied = 1;
		philo->data->satisfied_count++;
		pthread_mutex_unlock(&philo->data->data_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		pthread_mutex_lock(&philo->data->data_mutex);
		printf("%s%s🎯 Philosopher %d has completed"
			"%lld meals! (%lld/%d satisfied)%s\n", BOLD, GREEN, philo->id + 1,
			philo->meals_eaten, philo->data->satisfied_count,
			philo->data->philo_count, RESET);
		pthread_mutex_unlock(&philo->data->data_mutex);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
}
