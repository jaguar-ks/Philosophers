/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:53:01 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/26 17:37:51 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	main(int ac, char **av)
{
	t_nd	nd;

	if (ac == 6 || ac == 5)
		nd.inf = init_info(ac, av);
	else
		exit(error(-1));
	nd.phls = setting_up_table(nd.inf);
	start_the_feast(nd);
}
