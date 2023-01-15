/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:22:33 by ykruhlyk          #+#    #+#             */
/*   Updated: 2023/01/15 19:05:45 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_states (t_data *data, t_philo *philo, char *act)
{
	// pthread_mutex_lock(&data->dead);
	// if (data->death)
	// {	
	// 	pthread_mutex_unlock(&data->dead);
	// 	return ;
	// }
	// pthread_mutex_unlock(&data->dead);
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

int eating_time(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->dead);
	if (data->death)
	{	
		pthread_mutex_unlock(&data->dead);
		return 1;
	}
	pthread_mutex_unlock(&data->dead);
	pthread_mutex_lock(&data->fork[philo->fork_left]);
	print_states(data, philo, "has taken a fork");
	if (data->philo_num == 1)
		return (pthread_mutex_unlock(&data->fork[data->philo->fork_left]), 1);
	pthread_mutex_lock(&data->fork[philo->fork_right]);
	print_states(data, philo, "has taken a fork");
	print_states(data, philo, "is eating");
	pthread_mutex_lock(&data->eaten);
	philo->eat_num++;
	pthread_mutex_unlock(&data->eaten);
	pthread_mutex_lock(&data->meal);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&data->meal);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&data->fork[philo->fork_left]);
	pthread_mutex_unlock(&data->fork[philo->fork_right]);
	return (0);
}

void	sleeping_time(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->dead);
	if (data->death)
	{	
		pthread_mutex_unlock(&data->dead);
		return ;
	}
	pthread_mutex_unlock(&data->dead);
	print_states(data, philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	thinking_time(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->dead);
	if (data->death)
	{	
		pthread_mutex_unlock(&data->dead);
		return ;
	}
	pthread_mutex_unlock(&data->dead);
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
			{	
				pthread_mutex_lock(&structs->eaten);
				if (philos->eat_num == structs->lunch_num)
				{	
					pthread_mutex_unlock(&structs->eaten);
					return(NULL);
				}
				pthread_mutex_unlock(&structs->eaten);
			}
			pthread_mutex_lock(&structs->meal);
			if (timestamp() - philos[i].last_meal > philos[i].time_to_die)
			{
				pthread_mutex_unlock(&structs->meal);
				pthread_mutex_lock(&structs->dead);
				structs->death = 1;	
				pthread_mutex_unlock(&structs->dead);
				pthread_mutex_lock(&structs->print);
				printf("%lld %d is died \n", timestamp()- philos->start, philos->index);
				pthread_mutex_unlock(&structs->print);
				return(NULL);
			}
			pthread_mutex_unlock(&structs->meal);
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
	while (1)
	{
		pthread_mutex_lock(&data->dead);
		if(data->death)
		{
			pthread_mutex_unlock(&data->dead);
			break ;
		}
		pthread_mutex_unlock(&data->dead);
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
	// pthread_mutex_unlock(&structs->print);
	pthread_join(check, NULL);
	i = 0;
	while (i < structs->philo_num)
	{
		pthread_join(structs->thread[i], NULL);
		i++;
	}
	return (0);
}
