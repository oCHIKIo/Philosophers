/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:43:05 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/16 22:43:05 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000LL + tv.tv_usec / 1000LL);
}

void	sleep_precise(long long milliseconds)
{
	long long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < milliseconds)
		usleep(100);
}
