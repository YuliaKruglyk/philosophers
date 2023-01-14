/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:05:20 by ykruhlyk          #+#    #+#             */
/*   Updated: 2023/01/13 10:57:16 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	t;
	long long		cur;

	gettimeofday (&t, NULL);
	cur = ((t.tv_sec * 1000) + (t.tv_usec / 1000));
	return (cur);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = timestamp();
	while (timestamp() - start < time)
		usleep(100);
}
