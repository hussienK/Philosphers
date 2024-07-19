/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:37:58 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/14 12:46:36 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	returns the time in milliseconds,
	uses uint64 to gurrantee value is always in 64 bites
*/
uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, 0))
		return (0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

/*
	similar to atoi but to long type of var
*/
long	ft_ato_long(char const *str)
{
	long	sign;
	long	nb;

	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	nb = 0;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * sign);
}

/*
	returns max of 2 ints
*/
int	max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

/*
	returns min of 2 ints
*/
int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	destroy_mutexes(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_nb)
		pthread_mutex_destroy(&philo->fork[i++]);
	i = 0;
	pthread_mutex_destroy(&data->mutex_all_eat);
	pthread_mutex_destroy(&data->mutex_eat);
	pthread_mutex_destroy(&data->mutex_any_died);
	pthread_mutex_destroy(&data->mutex_print);
}
