/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 20:29:36 by mchemari          #+#    #+#             */
/*   Updated: 2025/09/28 21:27:02 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <unistd.h>

static int	take_fork(t_fork *fork, t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&fork->mutex);
		if (!fork->is_taken)
		{
			fork->is_taken = true;
			pthread_mutex_unlock(&fork->mutex);
			print_status(philo, "has taken a fork");
			return (1);
		}
		pthread_mutex_unlock(&fork->mutex);
		usleep(100);
	}
}

static void	release_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->is_taken = false;
	pthread_mutex_unlock(&fork->mutex);
}

static int	philo_eat(t_philo *philo)
{
	take_fork(philo->left_fork, philo);
	if (philo->data->nb_philos == 1)
	{
		ft_usleep(philo->data->t_die, philo->data);
		release_fork(philo->left_fork);
		return (0);
	}
	take_fork(philo->right_fork, philo);
	print_status(philo, "is eating");
	ft_usleep(philo->data->t_eat, philo->data);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	release_fork(philo->right_fork);
	release_fork(philo->left_fork);
	return (1);
}

static void	*run_routine(t_philo *philo)
{
	if (philo->data->nb_philos != 1)
		print_status(philo, "is thinking");
	if (philo->id % 2 != 1)
	{
		ft_usleep(philo->data->t_eat / 2, philo->data);
	}
	while (!is_dead(philo) && (philo->data->must_eat < 0
			|| philo->meals_eaten < philo->data->must_eat))
	{
		if (!philo_eat(philo))
			break ;
		if (is_dead(philo))
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->t_sleep, philo->data);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	bool	ready;

	philo = (t_philo *)arg;
	data = philo->data;
	ready = false;
	while (!ready)
	{
		if (is_dead(philo))
			return (NULL);
		pthread_mutex_lock(&data->ready_lock);
		ready = data->philo_ready;
		pthread_mutex_unlock(&data->ready_lock);
		usleep(100);
	}
	return (run_routine(philo));
}
