/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:43:14 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/17 12:50:18 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define DIM "\033[2m"
# define RED "\033[31m"
# define BOLD "\033[1m"
# define RESET "\033[0m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"
# define GREEN "\033[32m"
# define WHITE "\033[37m"
# define YELLOW "\033[33m"
# define BG_RED "\033[41m"
# define MAGENTA "\033[35m"
# define BG_GREEN "\033[42m"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					left_fork;
	int					right_fork;
	long long			last_meal_time;
	long long			meals_eaten;
	int					satisfied;
	int					has_forks;
	pthread_t			thread;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					philo_count;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	long long			must_eat_count;
	long long			sim_start_time;
	long long			sim_end_time;
	long long			total_meals;
	long long			satisfied_count;
	int					simulation_stop;
	int					death_occurred;
	pthread_mutex_t		*fork_mutexes;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		data_mutex;
	t_philo				*philosophers;
}						t_data;

typedef struct s_safe_atoi
{
	long long			res;
	int					has_digits;
	int					is_neg;
}						t_safe_atoi;

long long				get_time_ms(void);
void					print_banner(void);
void					print_footer(void);
void					eat_meal(t_philo *philo);
void					print_stats(t_data *data);
int						safe_atoi(const char *str);
void					wait_threads(t_data *data);
void					print_header(t_data *data);
void					create_threads(t_data *data);
void					release_forks(t_philo *philo);
int						acquire_forks(t_philo *philo);
void					*philosopher_routine(void *arg);
void					*death_monitor_routine(void *arg);
void					sleep_precise(long long milliseconds);
void					handle_single_philosopher(t_philo *philo);
void					print_action(t_philo *philo, const char *action);
int						validate_and_init(t_data *data, int argc, char **argv);

#endif
