/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:59:28 by marvin            #+#    #+#             */
/*   Updated: 2024/07/13 14:59:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	safely prints the current acion
*/
void	print_philo_actions(t_philo *philo, char *inst)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	if (*inst == 'd' || (!check_any_died(philo) && !check_all_ate(philo)))
	{
		printf("%lu ", get_time() - philo->data->program_start);
		printf("%d ", philo->id);
		printf("%s\n", inst);
	}
	pthread_mutex_unlock(&philo->data->mutex_print);
}

/*
	to set the death of a philo safely
*/
void	any_died(t_data *data)
{
	pthread_mutex_lock(&data->mutex_any_died);
	data->any_died = true;
	pthread_mutex_unlock(&data->mutex_any_died);
}

/*
	sets all philosphers as ate safely
*/
void	all_ate(t_data *data)
{
	pthread_mutex_lock(&data->mutex_all_eat);
	data->all_has_ate = true;
	pthread_mutex_unlock(&data->mutex_all_eat);
}

/*
	does checks over phio to check if any have died safely
*/
int	check_any_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_any_died);
	if (philo->data->any_died)
	{
		pthread_mutex_unlock(&philo->data->mutex_any_died);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->mutex_any_died);
	return (false);
}

/*
	does check over philos to check if any have ate safely
*/
int	check_all_ate(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_all_eat);
	if (philo->data->all_has_ate)
	{
		pthread_mutex_unlock(&philo->data->mutex_all_eat);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->mutex_all_eat);
	return (false);
}
