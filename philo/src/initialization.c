/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:01:14 by dev               #+#    #+#             */
/*   Updated: 2025/09/28 20:25:28 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdlib.h>
#include <stdio.h>

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].meal_lock, NULL) != 0)
			return (0);
		data->initialized_philos++;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
		i++;
	}
	return (1);
}

static int	init_mutexs(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_fork) * data->nb_philos);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i].mutex, NULL) != 0)
			return (0);
		data->initialized_forks++;
		data->forks[i].is_taken = false;
		i++;
	}
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (0);
	data->print_lock_initialized = true;
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (0);
	data->dead_lock_initialized = true;
	if (pthread_mutex_init(&data->ready_lock, NULL) != 0)
		return (0);
	data->ready_lock_initialized = true;
	return (1);
}

static void	set_initial_state(t_data *data)
{
	data->dead_flag = 0;
	data->philo_ready = false;
	data->initialized_forks = 0;
	data->initialized_philos = 0;
	data->print_lock_initialized = false;
	data->dead_lock_initialized = false;
	data->ready_lock_initialized = false;
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (!check_args(data, argc, argv))
		return (0);
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
	{
		printf("Error: malloc failed for philos\n");
		return (0);
	}
	set_initial_state(data);
	if (!init_mutexs(data))
	{
		printf("Error: mutex initialization failed");
		destroy_all(data);
		return (0);
	}
	if (!init_philos(data))
	{
		printf("Error: philo initialization failed\n");
		destroy_all(data);
		return (0);
	}
	return (1);
}
