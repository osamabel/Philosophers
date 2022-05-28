/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:35:05 by obelkhad          #+#    #+#             */
/*   Updated: 2022/05/28 19:03:10 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int finish_meal(t_data *data)
{
	int i;

	i = 0;
	if (data->nbr_must_eat == -1)
		return (1);
	while (i < data->nbr_philo)
	{
		if (data->philos[i].eat_times < data->nbr_must_eat)
			return (1);
		i++;
	}
	data->some_one_dead = 1;
	return (0);
}

int	lol(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo && data->philos[i].check)
		i++;
	if (i == data->nbr_philo)
		return (1);
	return (0);
}

void check_die(t_data *data)
{
	int	i;
	usleep(1000);
	while (!data->some_one_dead)
	{
		i = 0;
		while (i < data->nbr_philo)
		{
			usleep(1000);
			pthread_mutex_lock(&data->is_die);
			if (get_time() - data->philos[i].last_time_eat >= (size_t)data->t_die)
			{
				data->some_one_dead = 1;
				pthread_mutex_unlock(&data->is_die);
				monitoring(data, i, "died", 1);
				break;
			}
			pthread_mutex_unlock(&data->is_die);
			i++;
		}
	}
}

void	*routine(void *info)
{
	static int	i;
	t_data		*data;
	int			id;

	data = (t_data *)info;
	id = i;
	i++;
	pthread_mutex_lock(&data->is_printing);
	data->philos[id].last_time_eat = data->reference_time;
	pthread_mutex_unlock(&data->is_printing);
	if (id % 2)
		usleep(100);
	while (finish_meal(data) && !data->some_one_dead)
	{
		thinking(data, id);
		if (eating(data, id))
			break;
		sleeping(data, id);
	}
	return (NULL);
}

int	creation(t_data *data)
{
	int	i;

	i = 0;
	data->reference_time = get_time();
	while (i < data->nbr_philo)
	{
		if (pthread_create(&data->philos[i].philo, NULL, routine, (void *)data))
			return (4);
		i++;
	}
	if (data->nbr_philo == 1)
	{
		usleep(100);
		data->philos[0].check = 1;
	}
	check_die(data);
	i = -1;
	while (++i < data->nbr_philo)
	{
		if (pthread_join(data->philos[i].philo, NULL))
			return (1);
	}
	i = -1;
	while (++i < data->nbr_philo)
		pthread_mutex_destroy(&data->philos[i].my_forks);
	if (pthread_mutex_destroy(&data->is_printing))
		return (1);
	if (pthread_mutex_destroy(&data->is_eating))
		return (1);
	if (pthread_mutex_destroy(&data->is_die))
		return (1);
	return (0);
}