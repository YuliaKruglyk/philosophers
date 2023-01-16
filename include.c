/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:16:38 by ykruhlyk          #+#    #+#             */
/*   Updated: 2023/01/16 17:26:43 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_states(t_data *data, t_philo *philo, char *act)
{
	pthread_mutex_lock(&data->dead);
	if (data->death)
	{	
		pthread_mutex_unlock(&data->dead);
		return ;
	}
	pthread_mutex_unlock(&data->dead);
	pthread_mutex_lock(&data->print);
	pthread_mutex_lock(&data->dead);
	if (data->death)
	{	
		pthread_mutex_unlock(&data->print);
		pthread_mutex_unlock(&data->dead);
		return ;
	}
	pthread_mutex_unlock(&data->dead);
	printf("%lld %d %s\n", timestamp() - philo->start, philo->index, act);
	pthread_mutex_unlock(&data->print);
}

int	ft_free(t_data *structs)
{
	if (structs->philo)
		free (structs->philo);
	if (structs->fork)
		free (structs->fork);
	if (structs->thread)
		free (structs->thread);
	free (structs);
	return (1);
}

long long	ft_atoi(const char *str)
{
	int							i;
	int							pn;
	unsigned long long			num;
	unsigned long long			prev;

	i = 0;
	pn = 1;
	num = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		pn *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		prev = num;
		num = num * 10 + str[i++] - '0';
		if ((prev < 0 && num > 0) || (prev > 0 && num < 0))
			return ((pn == 1) * -1);
	}
	return (num * pn);
}

void	ft_destroy_mutex(t_data *structs)
{
	int	i;

	i = 0;
	while (i < structs->philo_num)
	{
		if (pthread_mutex_destroy(&structs->fork[i]))
			printf ("Mutex %d couldn't be destroyed. \n", i);
		i++;
	}
	pthread_mutex_destroy(&structs->print);
	pthread_mutex_destroy(&structs->eaten);
	pthread_mutex_destroy(&structs->meal);
	pthread_mutex_destroy(&structs->dead);
}
