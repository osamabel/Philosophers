/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onetimecall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:36:28 by obelkhad          #+#    #+#             */
/*   Updated: 2022/05/28 18:55:07 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_usleep(size_t time_sleep, size_t record)
{
	usleep(time_sleep * 0.95 * 1000);
	while (get_time() - record < time_sleep)
		usleep(100);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	result;

	minus = 1;
	result = 0;
	i = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i++] == '-')
			minus = -minus;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + str[i++] - '0';
		else
			return (-1);
	}
	return (result * minus);
}

int	parse_args(t_data *data, char **argv)
{
	data->nbr_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->nbr_must_eat = -1;
	if (argv[5])
	{
		if (ft_atoi(argv[5]) != -1)
			data->nbr_must_eat = ft_atoi(argv[5]);
		else
			return (1);
	}
	if (data->nbr_philo <= 0 || data->nbr_philo > 200 || data->t_die < 0 || data->t_eat < 0 || data->t_sleep < 0)
		return (1);
	return (0);
}

int initialing(t_data *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nbr_philo);
	if (!data->philos)
		return (1);
	while (i < data->nbr_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_times = 0;
		data->philos[i].is_eating = 0;
		if (pthread_mutex_init(&data->philos[i].my_forks, NULL))
			return (1);
		i++;
	}
	i = -1;
	while (++i < data->nbr_philo - 1)
		data->philos[i].next_forks = &data->philos[i + 1].my_forks;
	data->philos[data->nbr_philo - 1].next_forks = &data->philos[0].my_forks;
	if (pthread_mutex_init(&data->is_printing, NULL))
		return (1);
	if (pthread_mutex_init(&data->is_eating, NULL))
		return (1);
	if (pthread_mutex_init(&data->is_die, NULL))
		return (1);
	data->some_one_dead = 0;
	return (0);
}
