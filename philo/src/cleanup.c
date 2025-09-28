/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 22:27:02 by mchemari          #+#    #+#             */
/*   Updated: 2025/09/28 11:54:20 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdlib.h>

void	destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->initialized_philos)
	{
		pthread_mutex_destroy(&data->philos[i].meal_lock);
		i++;
	}
	i = 0;
	while (i < data->initialized_forks)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
	if (data->print_lock_initialized)
		pthread_mutex_destroy(&data->print_lock);
	if (data->dead_lock_initialized)
		pthread_mutex_destroy(&data->dead_lock);
	if (data->ready_lock_initialized)
		pthread_mutex_destroy(&data->ready_lock);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}
