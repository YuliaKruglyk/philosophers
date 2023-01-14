/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:58:54 by ykruhlyk          #+#    #+#             */
/*   Updated: 2023/01/13 10:07:12 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> 
# include <unistd.h> 
# include <stdio.h> 
# include <stdlib.h> 
# include <pthread.h>
# include <sys/time.h> 

# define Y	"\033[33m"
# define R	"\033[31m"
# define G	"\033[32m"
# define B	"\033[34m"

typedef struct s_philo
{
	int				index;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_num;
	int				fork_left;
	int				fork_right;
	long long		start;
	long long		last_meal;
	struct s_data	*table;
}	t_philo;

typedef struct s_data
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				lunch_num;
	int				death;
	long long		start;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	t_philo			*philo;
}	t_data;

long long	ft_atoi(const char *str);
int			ft_free(t_data *structs);
int			parse_arg(int ac, char **av);
t_data		*init_struct(int ac, char **av);
int			malloc_for_everybody(t_data *structs);
int 		init_philo(t_data *structs);
long long	timestamp(void);
void		ft_usleep(long long time);
void		ft_destroy_mutex(t_data *structs);
void		print_states (t_data *data, t_philo *philo, char *act);
int 		eating_time(t_data *data, t_philo *philo);
void		sleeping_time(t_data *data, t_philo *philo);
void		thinking_time(t_data *data, t_philo *philo);
void		*death_time(void *temp);
int			philo_routine(t_data *structs);

#endif
