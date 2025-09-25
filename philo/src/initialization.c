/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:01:14 by dev               #+#    #+#             */
/*   Updated: 2025/09/25 19:21:11 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdlib.h>

static int	init_philos(t_data *data)
{
    int	i;

    i = 0;
    while (i < data->nb_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal_time = -1;
        data->philos[i].data = data;
        if (pthread_mutex_init(&data->philos[i].meal_lock, NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&data->philos[i].meal_lock);
            return (0);
        }
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
        {
			while (--i >= 0)
                pthread_mutex_destroy(&data->forks[i].mutex);
            free(data->forks);
            return (0);
		}
        data->forks[i].is_taken = false;
        i++;
    }
    if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (0);
    if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (0);
    return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (!check_args(data, argc, argv))
		return (0);
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		return (0);
	data->dead_flag = 0;
	data->philo_ready = false;
	if (!init_mutexs(data))
    {
        free(data->philos);
        return (0);
    }
    init_philos(data);
	return (1);
}