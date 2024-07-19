/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:14:20 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/14 11:14:21 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	-called after eating, for norminette
*/
void	end_eat(t_philo *self)
{
	print_philo_actions(self, "is sleeping");
	pthread_mutex_unlock(&self->fork[max (self->left_fork_id,
			self->right_fork_id)]);
	pthread_mutex_unlock(&self->fork[min (self->left_fork_id,
			self->right_fork_id)]);
	wait_duration(self->data->time_to_sleep);
}

/*
	called each time a philospher wants to eat
	-locks and unlocks both forks
	-locks the eating_check for safe updating of last_eat_timer
*/
int	philo_eats(t_philo *self)
{
	pthread_mutex_lock(&self->fork[min(self->left_fork_id,
			self->right_fork_id)]);
	print_philo_actions(self, "has taken a fork");
	if (self->left_fork_id == self->right_fork_id)
	{
		pthread_mutex_unlock(&self->fork[min(self->left_fork_id,
				self->right_fork_id)]);
		return (1);
	}
	pthread_mutex_lock(&self->fork[max(self->left_fork_id,
			self->right_fork_id)]);
	print_philo_actions(self, "has taken a fork");
	print_philo_actions(self, "is eating");
	pthread_mutex_lock(&self->data->mutex_eat);
	self->last_meal = get_time();
	self->meals_counter++;
	pthread_mutex_unlock(&self->data->mutex_eat);
	if (check_all_ate(self))
	{
		end_eat (self);
		return (1);
	}
	wait_duration(self->data->time_to_eat);
	end_eat (self);
	return (0);
}

/*
	The thread of a philospher
	-starts the whole cycle of eating, thinking, sleeping until
	a philo dies
	-philos with odd indices start executing later on to minimize deadlocks
*/
void	*philo_func(void *arg)
{
	t_philo	*self;

	self = (t_philo *) arg;
	if (self->id % 2 == 0)
	{
		print_philo_actions(self, "is thinking");
		wait_duration(self->data->time_to_eat);
	}
	while (1)
	{
		if (check_any_died(self))
			break ;
		if (philo_eats (self) != 0)
			break ;
		print_philo_actions(self, "is thinking");
		wait_duration(self->data->time_to_think);
	}
	return (NULL);
}

/*
	checks if the program ended because all philosphers ate apropiatly
*/
bool	perform_eat_checks(t_philo *philo, t_data *data)
{
	int	i;
	int	done;
	int	meals_count;

	if (data->nb_times_to_eat == -1)
		return (false);
	i = -1;
	done = -1;
	while (++i < data->philo_nb)
	{
		pthread_mutex_lock(&philo->data->mutex_eat);
		meals_count = philo[i].meals_counter;
		pthread_mutex_unlock(&philo->data->mutex_eat);
		if (meals_count >= data->nb_times_to_eat)
			if (++done == data->philo_nb - 1)
				return (true);
		usleep (50);
	}
	return (false);
}

/*
	a smarter version of sleep
*/
void	wait_duration(uint64_t msec)
{
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
	usleep(msec * 50);
}
