/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:59:14 by ykruhlyk          #+#    #+#             */
/*   Updated: 2023/01/16 17:22:43 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*structs;

	if (parse_arg(argc, argv))
		return (1);
	structs = init_struct(argc, argv);
	if (!structs)
		return (ft_free(structs));
	if (malloc_for_everybody(structs))
		return (ft_free(structs));
	if (init_philo(structs))
		return (ft_free(structs));
	philo_routine(structs);
	ft_destroy_mutex(structs);
	ft_free(structs);
	return (0);
}
