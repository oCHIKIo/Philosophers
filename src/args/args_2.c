/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:40:03 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/16 22:40:04 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	parse_digits(const char *str, t_safe_atoi *x)
{
	while (*str >= '0' && *str <= '9')
	{
		x->res = x->res * 10 + (*str - '0');
		x->has_digits = 1;
		if (x->res > INT_MAX)
		{
			printf("%s%sError: numeric overflow%s\n", BOLD, RED, RESET);
			return (-1);
		}
		str++;
	}
	if (*str || !x->has_digits)
		return (-1);
	return (0);
}

int	safe_atoi(const char *str)
{
	t_safe_atoi	x;

	x.res = 0;
	x.has_digits = 0;
	x.is_neg = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			x.is_neg = 1;
		str++;
	}
	if (parse_digits(str, &x) == -1)
		return (-1);
	if (x.is_neg)
		return (-(int)x.res);
	else
		return ((int)x.res);
}
