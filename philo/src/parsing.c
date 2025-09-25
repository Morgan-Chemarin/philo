/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:49:36 by dev               #+#    #+#             */
/*   Updated: 2025/09/25 17:13:15 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>

static int	is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

static int	is_number(const char *str)
{
    int	i;

    i = 0;
    if (str[i] == '+')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (!is_digit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

static int	check_valid_number(char *to_convert, int *data, char *error_msg)
{
    int	nb;
	// check_overflow ?
    if (!is_number(to_convert))
    {
        printf("%s", error_msg);
        return (0);
    }
    nb = ft_atoi(to_convert);
    if (nb < 0)
    {
        printf("%s", error_msg);
        return (0);
    }
    *data = nb;
    return (1);
}

int	check_args(t_data *data, int argc, char **argv)
{
	if (!check_valid_number(argv[1], &data->nb_philos, ERR_NB_PHILOS))
		return (0);
	if (data->nb_philos == 0)
    {
        printf("%s", ERR_NB_PHILOS);
        return (0);
    }
	if (!check_valid_number(argv[2], &data->t_die, ERR_T_DIE))
		return (0);
	if (!check_valid_number(argv[3], &data->t_eat, ERR_T_EAT))
		return (0);
	if (!check_valid_number(argv[4], &data->t_sleep, ERR_T_SLEEP))
		return (0);
	if (argc == 6)
	{
		if (!check_valid_number(argv[5], &data->must_eat, ERR_MUST_EAT))
			return (0);
	}
	else
		data->must_eat = -1;
	return (1);
}
