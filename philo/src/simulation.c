/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:17:24 by dev               #+#    #+#             */
/*   Updated: 2025/09/25 19:50:15 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	monitoring(void *arg)
{
	t_data	*data;
	
	data = (t_data *)arg;
    // Logique de surveillance à implémenter ici
    // - Vérifier si un philosophe est mort (get_time() - philo->last_meal_time > data->t_die)
    // - Vérifier si tous les philosophes ont mangé `must_eat` fois
    // - Mettre `dead_flag` à 1 si une condition est remplie pour arrêter la simulation
}

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	data->start_time = get_time();
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(data->philos[i].thread, NULL);
			return (0);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, &monitoring, data) != 0)
        return (0);
	data->philo_ready = true;
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (1);
}
