/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:45:13 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/14 11:11:29 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "../mylib/ft_printf/includes/ft_printf.h"
# include "../mylib/get_next_line/includes/get_next_line.h"
# include "../mylib/libft/includes/libft.h"
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <aio.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_data
{
	int					philo_nb;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_think;
	int					nb_times_to_eat;

	uint64_t			program_start;
	bool				all_has_ate;
	bool				any_died;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		mutex_eat;
	pthread_mutex_t		mutex_all_eat;
	pthread_mutex_t		mutex_any_died;
}		t_data;

typedef struct s_philo
{
	int					id;
	uint64_t			last_meal;
	int					meals_counter;
	int					left_fork_id;
	int					right_fork_id;
	pthread_mutex_t		*fork;
	t_data				*data;
}	t_philo;

long			ft_ato_long(char const *str);
int				min(int a, int b);
int				max(int a, int b);

void			print_philo_actions(t_philo *philo, char *inst);
void			any_died(t_data *data);
void			all_ate(t_data *data);
int				check_any_died(t_philo *philo);
int				check_all_ate(t_philo *philo);

uint64_t		get_time(void);
uint64_t		ft_rel_time(uint64_t begin);
void			wait_duration(uint64_t msec);

void			*philo_func(void *arg);

int				philosophers(t_philo *philo, t_data *data);

int				ft_init_philo(t_philo **philo, t_data *data);
int				ft_init_data_mutexes(t_data **data);
int				ft_init_data(t_data **data, int ac, char const *const *av);
int				fill_input(t_philo **p, t_data **d, int argc, char **argv);

int				check_for_args(int argc, char **argv);
void			destroy_mutexes(t_philo *philo, t_data *data);
bool			perform_eat_checks(t_philo *philo, t_data *data);

#endif