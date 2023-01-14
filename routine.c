/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:22:33 by ykruhlyk          #+#    #+#             */
/*   Updated: 2023/01/13 11:03:19 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_states (t_data *data, t_philo *philo, char *act)
{
	if (data->death)
		return ;
	pthread_mutex_lock(&data->print);
	if (data->death)
		return ;
	printf("%lld %d %s\n", timestamp() - philo->start, philo->index, act);
	pthread_mutex_unlock(&data->print);
}

int eating_time(t_data *data, t_philo *philo)
{
	if (data->death)
		return (1);
	pthread_mutex_lock(&data->fork[philo->fork_left]);
	print_states(data, philo, "has taken a fork");
	if (data->philo_num == 1)
		return (pthread_mutex_unlock(&data->fork[data->philo->fork_left]), 1);
	pthread_mutex_lock(&data->fork[philo->fork_right]);
	print_states(data, philo, "has taken a fork");
	print_states(data, philo, "is eating");
	philo->eat_num++;
	philo->last_meal = timestamp();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&data->fork[philo->fork_left]);
	pthread_mutex_unlock(&data->fork[philo->fork_right]);
	return (0);
}

void	sleeping_time(t_data *data, t_philo *philo)
{
	if (data->death)
		return ;
	print_states(data, philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	thinking_time(t_data *data, t_philo *philo)
{
	if (data->death)
		return ;
	print_states(data, philo, "is thinking");
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
				if (philos->eat_num == structs->lunch_num)
					return(NULL);
			if (timestamp() - philos[i].last_meal > philos[i].time_to_die)
			{
				structs->death = 1;
				pthread_mutex_lock(&structs->print);
				printf("%lld %d is died \n", timestamp()- philos->start, philos->index);
				return(NULL);
			}
		
		}
	}
	return (NULL);
}

void	*life_start(void	*temp)
{
	t_philo *philo;
	t_data	*data;

	philo = (t_philo *)temp;
	data = philo->table;
	if (philo->index % 2 == 0)
	{
		print_states(data, philo, "is thinking");
		usleep (50);
	}
	while (!data->death)
	{
		if (data->lunch_num && philo->eat_num == data->lunch_num)
			return (NULL);
		if (eating_time(data, philo))
			return (NULL);
		sleeping_time(data, philo);
		thinking_time(data, philo);
	}
	return (NULL);
}

int	philo_routine(t_data *structs)
{
	int			i;
	pthread_t	check;

	i = 0;
	structs->start = timestamp();
	while (i < structs->philo_num)
	{
		structs->philo[i].start = structs->start;
		structs->philo[i].last_meal = structs->start;
		i++;
	}
	i = 0;
	while (i < structs->philo_num)
	{	
		pthread_create(&structs->thread[i], NULL, &life_start, &structs->philo[i]);
		i++;
	}
	pthread_create(&check, NULL, &death_time, structs);
	pthread_mutex_unlock(&structs->print);
	pthread_join(check, NULL);
	i = 0;
	while (i < structs->philo_num)
	{
		pthread_join(structs->thread[i], NULL);
		i++;
	}
	return (0);
}
