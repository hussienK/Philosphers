/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:18:55 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/14 11:13:55 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	frees all the input when done executing
*/
void	free_input(t_philo *philo, t_data *data)
{
	if (data)
		free(data);
	if (philo && philo->fork)
		free(philo->fork);
	if (philo)
		free(philo);
}

/*
	starts the whole program
*/
int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	data = NULL;
	philo = NULL;
	if (!check_for_args(argc, argv))
		return (1);
	if (!fill_input(&philo, &data, argc, argv))
		return (free_input(philo, data), 1);
	if (philosophers(philo, data) != 0)
		return (free_input(philo, data), 1);
	free_input(philo, data);
	return (0);
}
