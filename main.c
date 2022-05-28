/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:59:20 by obelkhad          #+#    #+#             */
/*   Updated: 2022/05/28 17:11:22 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (parse_args(&data, argv))
		{
			write(2, "invalid arguments\n", 19);
			return(1);
		}
		if (initialing(&data))
			return(1);
		if (creation(&data))
		{
			free(data.philos);
			return (10);
		}
		else
			free(data.philos);
	}
	else
	{
		write(2, "invalid number of arguments\n", 28);
		return(1);
	}
	return(0);
}