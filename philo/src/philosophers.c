/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:10:44 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/14 11:31:05 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Updates state of the program constantly
	-responsible for stopping the program from quiting while threads
	are executign aswell (the main loop)
*/
void	run_loop(t_philo *philo, t_data *data)
{
	int				i;
	uint64_t		l_meal;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mutex_eat);
		l_meal = philo[i].last_meal;
		pthread_mutex_unlock(&data->mutex_eat);
		if (l_meal && perform_eat_checks(philo, data))
		{
			all_ate (data);
			break ;
		}
		if (l_meal && get_time () - l_meal > (uint64_t)data->time_to_die)
		{
			any_died(data);
			print_philo_actions(&philo[i], "died");
			break ;
		}
		i = (i + 1) % data->philo_nb;
		usleep (200);
	}
}

/*
	creates all the philosopher threads
*/
pthread_t	*create_philos(t_philo *philo, t_data *data)
{
	int			i;
	pthread_t	*threads;

	threads = malloc(sizeof (pthread_t) * (size_t)data->philo_nb);
	if (threads == NULL)
		return (NULL);
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create(&threads[i], 0, philo_func, (void *)&philo[i]))
		{
			while (i--)
				pthread_join(threads[i], NULL);
			return (free(threads), NULL);
		}
		i++;
	}
	return (threads);
}

/*
	-manages the main execution loops
	-creates the philo threads and starts their execution
*/
int	philosophers(t_philo *philo, t_data *data)
{
	int			i;
	pthread_t	*threads;

	threads = create_philos(philo, data);
	if (!threads)
		return (1);
	run_loop(philo, data);
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
		i++;
	}
	return (destroy_mutexes(philo, data), free(threads), 0);
}
