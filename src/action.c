/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:24:07 by obelkhad          #+#    #+#             */
/*   Updated: 2022/05/28 19:12:27 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t get_time(void)
{
	unsigned long	time_ms;
	struct timeval	current;

	gettimeofday(&current, NULL);
	time_ms = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (time_ms);
}

void monitoring(t_data *data, int id, char *msg, int bol)
{
	static int stop;

	pthread_mutex_lock(&data->is_printing);
	if (stop == 0)
		printf("%lu %d %s\n", get_time() - data->reference_time, data->philos[id].id, msg);
	else
	{
		pthread_mutex_unlock(&data->is_printing);
		return;
	}
	if (bol)
		stop = 1;
	pthread_mutex_unlock(&data->is_printing);
}

int eating(t_data *data, int id)
{
	pthread_mutex_lock(&data->philos[id].my_forks);
	monitoring(data, id, "has taken a fork", 0);
	if (data->nbr_philo == 1)
		return (1);
	pthread_mutex_lock(data->philos[id].next_forks);
	monitoring(data, id, "has taken a fork", 0);
	data->philos[id].last_time_eat = get_time();
	data->philos[id].eat_times++;
	monitoring(data, id, "is eating", 0);
	ft_usleep(data->t_eat,data->philos[id].last_time_eat);
	pthread_mutex_unlock(data->philos[id].next_forks);
	pthread_mutex_unlock(&data->philos[id].my_forks);
	return (0);
}

void sleeping(t_data *data, int id)
{
	monitoring(data, id, "is sleeping", 0);
	data->philos[id].last_time_sleep = get_time();
	ft_usleep(data->t_sleep,data->philos[id].last_time_sleep);
}

void thinking(t_data *data, int id)
{
	monitoring(data, id, "is thinking", 0);
}