/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to_die.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:23:55 by ykruhlyk          #+#    #+#             */
/*   Updated: 2023/01/16 17:59:02 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_data *data)
{
	pthread_mutex_lock(&data->dead);
	if (data->death)
	{	
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	return (0);
}

int	eaten_check(t_data *structs, t_philo *philos)
{	
	pthread_mutex_lock(&structs->eaten);
	if (philos->eat_num == structs->lunch_num)
	{	
		pthread_mutex_unlock(&structs->eaten);
		return (1);
	}
	pthread_mutex_unlock(&structs->eaten);
	return (0);
}

int	meal_check(t_data *structs, t_philo *philos, int i)
{	
	pthread_mutex_lock(&structs->meal);
	if (timestamp() - philos[i].last_meal > philos[i].time_to_die)
	{
		pthread_mutex_unlock(&structs->meal);
		pthread_mutex_lock(&structs->dead);
		structs->death = 1;
		pthread_mutex_unlock(&structs->dead);
		pthread_mutex_lock(&structs->print);
		printf("%lld %d is died \n", timestamp() - philos->start, philos->index);
		pthread_mutex_unlock(&structs->print);
		return (1);
	}
	pthread_mutex_unlock(&structs->meal);
	return (0);
}

void	*death_time(void *temp)
{
	t_data	*structs;
	t_philo	*philos;
	int		i;

	structs = temp;
	philos = structs->philo;
	while (1)
	{
		i = -1;
		while (++i < structs->philo_num)
		{
			if (structs->lunch_num)
			{	
				if (eaten_check(structs, philos))
					return (NULL);
			}
			if (meal_check(structs, philos, i))
				return (NULL);
		}
	}
	return (NULL);
}
