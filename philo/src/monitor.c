/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:12:43 by mchemari          #+#    #+#             */
/*   Updated: 2025/09/28 21:48:35 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <unistd.h>

static int	check_death(t_data *data)
{
	int	i;

	i = 0;
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
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		i++;
	}
	return (0);
}

static int	check_all_eaten(t_data *data)
{
	int	i;
	int	has_all_eaten;

	i = 0;
	has_all_eaten = 0;
	if (data->must_eat < 0)
		return (0);
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_lock);
		if (data->philos[i].meals_eaten >= data->must_eat)
			has_all_eaten++;
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		i++;
	}
	if (has_all_eaten == data->nb_philos)
	{
		pthread_mutex_lock(&data->dead_lock);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data) || check_all_eaten(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}
