/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:53:11 by dev               #+#    #+#             */
/*   Updated: 2025/09/28 21:48:26 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ERR_NB_PHILOS "Error: invalid number_of_philosophers\n"
# define ERR_T_DIE "Error: invalid time_to_die\n"
# define ERR_T_EAT "Error: invalid time_to_eat\n"
# define ERR_T_SLEEP "Error: invalid time_to_sleep\n"
# define ERR_MUST_EAT "Error: invalid must_eat\n"

# include <pthread.h>
# include <stdbool.h>

typedef struct s_data	t_data;

typedef struct s_fork
{
	bool			is_taken;
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
	int				initialized_forks;
	int				initialized_philos;
	pthread_mutex_t	print_lock;
	bool			print_lock_initialized;
	pthread_mutex_t	dead_lock;
	bool			dead_lock_initialized;
	pthread_mutex_t	ready_lock;
	bool			ready_lock_initialized;
};

// initialization.c
int			init_data(t_data *data, int argc, char **argv);

// parsing.c
int			check_args(t_data *data, int argc, char **argv);

// routine.c
void		*philo_routine(void *arg);

// simulation.c
int			start_simulation(t_data *data);

// utils.c
int			ft_atoi(const char *str);
int			is_dead(t_philo *philo);
long long	get_time(void);
void		print_status(t_philo *philo, char *status);
void		ft_usleep(long long time, t_data *data);

// cleanup.c
void		destroy_all(t_data *data);

// monitor.c
void		*monitoring(void *arg);

#endif