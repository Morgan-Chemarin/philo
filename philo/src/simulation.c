/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:17:24 by dev               #+#    #+#             */
/*   Updated: 2025/09/28 12:12:57 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <unistd.h>
#include <stdio.h>

static void	*monitoring(void *arg)
{
	t_data	*data;
	int		i;
	int		has_all_eaten;

	data = (t_data *)arg;
	while (!data->dead_flag)
	{
		i = 0;
		has_all_eaten = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_lock(&data->philos[i].meal_lock);
			if (get_time() - data->philos[i].last_meal_time > data->t_die)
			{
				pthread_mutex_unlock(&data->philos[i].meal_lock);
				print_status(&data->philos[i], "died");
				pthread_mutex_lock(&data->dead_lock);
				data->dead_flag = 1;
				pthread_mutex_unlock(&data->dead_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i].meal_lock);
			pthread_mutex_lock(&data->philos[i].meal_lock);
			if (data->must_eat > 0 && data->philos[i].meals_eaten >= data->must_eat)
				has_all_eaten++;
			pthread_mutex_unlock(&data->philos[i].meal_lock);
			i++;
		}
		if (data->must_eat > 0 && has_all_eaten == data->nb_philos)
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	data->start_time = get_time();
	while (i < data->nb_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				&data->philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(data->philos[i].thread, NULL);
			return (0);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, &monitoring, data) != 0)
	{
		while (--i >= 0)
			pthread_join(data->philos[i].thread, NULL);
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
