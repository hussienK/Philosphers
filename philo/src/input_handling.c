/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:38:53 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/14 11:11:18 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	loops through all the philos and inits their data
*/
int	create_philosphers(t_philo **philo, t_data *data)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = malloc (sizeof(pthread_mutex_t) * ((size_t)data->philo_nb));
	if (fork == NULL)
		return (0);
	i = 0;
	while (i < data->philo_nb)
		pthread_mutex_init(&fork[i++], NULL);
	i = 0;
	while (i < data->philo_nb)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].last_meal = data->program_start;
		(*philo)[i].meals_counter = 0;
		(*philo)[i].left_fork_id = i;
		(*philo)[i].right_fork_id = (i + 1) % data->philo_nb;
		(*philo)[i].fork = fork;
		(*philo)[i].data = data;
		i++;
	}
	return (1);
}

/*
	create the required mutexes to prevent data races
*/
int	create_mutexes(t_data **data)
{
	pthread_mutex_init((&(*data)->mutex_eat), NULL);
	pthread_mutex_init((&(*data)->mutex_all_eat), NULL);
	pthread_mutex_init((&(*data)->mutex_any_died), NULL);
	pthread_mutex_init((&(*data)->mutex_print), NULL);
	return (0);
}

/*
	inits the programs run data
*/
int	fill_data(t_data **data, int argc, char **argv)
{
	(*data)->program_start = get_time ();
	(*data)->philo_nb = (int)ft_ato_long (argv[1]);
	(*data)->time_to_die = (int)ft_ato_long (argv[2]);
	(*data)->time_to_eat = (int)ft_ato_long (argv[3]);
	(*data)->time_to_sleep = (int)ft_ato_long (argv[4]);
	(*data)->time_to_think = 0;
	if (((*data)->philo_nb % 2)
		&& ((*data)->time_to_eat > (*data)->time_to_sleep))
		(*data)->time_to_think = 1
			+ ((*data)->time_to_eat - (*data)->time_to_sleep);
	if (argc == 5)
		(*data)->nb_times_to_eat = -1;
	if (argc == 6)
		(*data)->nb_times_to_eat = (int)ft_ato_long(argv[5]);
	(*data)->all_has_ate = false;
	(*data)->any_died = false;
	if (create_mutexes(data))
		return (0);
	return (1);
}

/*
	starts the whole input check process
*/
int	fill_input(t_philo **philo, t_data **data, int argc, char **argv)
{
	*data = (t_data *)malloc(sizeof (t_data));
	if (*data == NULL)
		return (0);
	if (!fill_data(data, argc, argv))
		return (0);
	*philo = (t_philo *)malloc(sizeof (t_philo) * (size_t)(*data)->philo_nb);
	if (*philo == NULL)
		return (0);
	(*philo)->fork = NULL;
	if (!create_philosphers(philo, *data))
		return (0);
	return (1);
}

/*
	does checks over user inputs
*/
int	check_for_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Error, Usage: ", 2);
		ft_putstr_fd("./philosphers nb_of_phil time_to_die time_to_eatt", 2);
		ft_putstr_fd("time_to_sleepp (optional)nb_time_philo_eats\n", 2);
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!ft_str_numeric(argv[i]))
		{
			ft_putstr_fd("All arguments must be numeric\n", 2);
			return (0);
		}
		if (argv[i++][0] == '-')
		{
			ft_putstr_fd("Please enter numbers in valid range\n", 2);
			return (0);
		}
	}
	return (1);
}
