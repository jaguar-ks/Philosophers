/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:53:01 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/25 15:16:11 by deman_wolf       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	main(int ac, char **av)
{
	t_inf	inf;

	if (ac == 6 || ac == 5)
		inf = init_info(ac, av);
	else
		exit(error(-1));
	inf.phls = setting_up_table(inf);
	
}
