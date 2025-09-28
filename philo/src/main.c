/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:54:02 by dev               #+#    #+#             */
/*   Updated: 2025/09/28 20:23:12 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo nb_philos t_die t_eat t_sleep [must_eat]\n");
		return (1);
	}
	if (!init_data(&data, argc, argv))
		return (1);
	if (!start_simulation(&data))
		return (1);
	destroy_all(&data);
	return (0);
}
