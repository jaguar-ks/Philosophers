/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:53:01 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/24 20:18:08 by deman_wolf       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	main(int ac, char **av)
{
	t_inf	inf;
	t_philo *philos;

	if (ac == 6 || ac == 5)
		inf = init_info(ac, av);
	else
		exit(error(-1));
	philos = setting_up_table(inf);
	while (1)
	{
		printf("ph[%d]\n",philos->philo_id);
		if (philos->philo_id == inf.nb_ph)
			break ;
		philos = philos->nxt;
	}
}
