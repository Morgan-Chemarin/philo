/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:17:24 by dev               #+#    #+#             */
/*   Updated: 2025/09/28 20:20:39 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <unistd.h>
#include <stdio.h>

static void	set_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead_flag = 1;
	pthread_mutex_unlock(&data->dead_lock);
}

static void	join_all_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

static int	create_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				&data->philos[i]) != 0)
		{
			printf("Error: thread creation failed for philo %d\n", i + 1);
			set_dead(data);
			while (--i >= 0)
				pthread_join(data->philos[i].thread, NULL);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	create_threads(t_data *data, pthread_t *monitor)
{
	data->start_time = get_time();
	if (!create_philo_threads(data))
		return (0);
	if (pthread_create(monitor, NULL, &monitoring, data) != 0)
	{
		printf("Error: thread creation failed for monitor\n");
		set_dead(data);
		join_all_philos(data);
		return (0);
	}
	return (1);
}

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	if (!create_threads(data, &monitor_thread))
	{
		destroy_all(data);
		return (0);
	}
	pthread_mutex_lock(&data->ready_lock);
	data->philo_ready = true;
	pthread_mutex_unlock(&data->ready_lock);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (1);
}
