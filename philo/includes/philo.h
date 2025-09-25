/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:53:11 by dev               #+#    #+#             */
/*   Updated: 2025/09/25 19:19:31 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# define ERR_NB_PHILOS "Error: invalid number_of_philosophers\n"
# define ERR_T_DIE "Error: invalid time_to_die\n"
# define ERR_T_EAT "Error: invalid time_to_eat\n"
# define ERR_T_SLEEP "Error: invalid time_to_sleep\n"
# define ERR_MUST_EAT "Error: invalid number_of_times_each_philosopher_must_eat\n"

# include <pthread.h>
# include <stdbool.h>

typedef struct s_data t_data;

typedef struct s_fork
{
	bool				is_taken;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
    int				id;
    int				meals_eaten;
    long long		last_meal_time;
    pthread_t		thread;
    t_fork			*left_fork;
    t_fork			*right_fork;
    pthread_mutex_t	meal_lock;
    struct s_data	*data;
}	t_philo;

struct s_data
{
	int				nb_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				dead_flag;
	bool			philo_ready;
    long long		start_time;
    t_philo			*philos;
    t_fork			*forks;
    pthread_mutex_t	print_lock;
    pthread_mutex_t	dead_lock;
};

// initialization.c
int	init_data(t_data *data, int argc, char **argv);

// parsing.c
int	check_args(t_data *data, int argc, char **argv);

// utils.c
int			ft_atoi(const char *str);
long long	get_time(void);

# endif