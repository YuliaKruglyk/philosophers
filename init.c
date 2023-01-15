/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:19:31 by ykruhlyk          #+#    #+#             */
/*   Updated: 2023/01/15 19:06:58 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_arg(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf(R "Invalid number of arguments.\n");
		return (1);
	}
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 
			|| ft_atoi(av[4]) <= 0)
	{
		printf(R "Invalid arguments.\n");
		return (1);
	}
	if (ac == 6 && ft_atoi(av[5]) <= 0)
	{
		printf(R "Invalid arguments.\n");
		return (1);
	}
	return (0);
}

t_data *init_struct(int ac, char **av)
{
	t_data	*table;
	table = malloc(sizeof(t_data));
	if (!table)
		return (NULL);
	table->philo_num = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->lunch_num = ft_atoi(av[5]);
	else 
		table->lunch_num = 0;
	table->death = 0;
	table->start = 0;
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->meal, NULL);
	pthread_mutex_init(&table->eaten, NULL);
	pthread_mutex_init(&table->dead, NULL);
	table->thread = NULL;
	table->philo = NULL;
	table->fork = NULL;
	return (table);
}

int	malloc_for_everybody(t_data *structs)
{
	structs->philo = malloc(sizeof(t_philo) * structs->philo_num);
	if (!structs->philo)
		return (1);
	structs->fork = malloc(sizeof(pthread_mutex_t) * structs->philo_num);
	if (!structs->fork)
		return (1);
	structs->thread = malloc(sizeof(pthread_t) * structs->philo_num);
	if (!structs->thread)
		return (1);
	return (0);
}

int init_philo(t_data *structs)
{
	int i;

	i = 0;
	while (i < structs->philo_num)
	{
		structs->philo[i].index = i + 1;
		structs->philo[i].time_to_die = structs->time_to_die;
		structs->philo[i].time_to_eat = structs->time_to_eat;
		structs->philo[i].time_to_sleep = structs->time_to_sleep;
		structs->philo[i].eat_num = 0;
		structs->philo[i].fork_left = i;
		if (i < structs->philo_num - 1)
			structs->philo[i].fork_right = i + 1;
		else
			structs->philo[i].fork_right = 0;
		structs->philo[i].last_meal = 0;
		structs->philo[i].table = structs;
		i++;
	}
	i = 0;
	while (i < structs->philo_num)
		if (pthread_mutex_init(&structs->fork[i++], NULL))
			return (1);
	return (0);
}
