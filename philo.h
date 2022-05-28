/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:02:45 by obelkhad          #+#    #+#             */
/*   Updated: 2022/05/28 14:30:56 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	int				eat_times;
	int				is_eating;
	size_t			last_time_eat;
	size_t			last_time_sleep;
	int				check;
	pthread_mutex_t	my_forks;
	pthread_mutex_t	*next_forks;
}	t_philo;

typedef struct s_data
{
	int				nbr_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nbr_must_eat;
	int				some_one_dead;
	size_t			reference_time;
	t_philo			*philos;
	pthread_mutex_t	is_printing;
	pthread_mutex_t	is_eating;
	pthread_mutex_t	is_die;
}	t_data;


int		ft_atoi(const char *str);
int		parse_args(t_data *data, char **argv);
int 	initialing(t_data *data);
int		creation(t_data *data);
size_t	get_time(void);
void	monitoring(t_data *data, int id, char *msg, int bol);
int		eating(t_data *data, int id);
void	sleeping(t_data *data, int id);
void	thinking(t_data *data, int id);
void	check_die(t_data *data);
void	ft_usleep(size_t time_sleep, size_t record);
#endif
