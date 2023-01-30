/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:53:01 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/30 16:57:43 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	main(int ac, char **av)
{
	t_nd	nd;
	// int id;

	if (ac == 6 || ac == 5)
		nd.inf = init_info(ac, av);
	else
		exit(error(-1));
	nd.phls = setting_up_table(nd.inf);
	// id = nd.phls->philo_id;
	// while (1)
	// {
	// 	printf("ph_id[%d] | st[%c] | mc[%d] | sc[%d] | nc[%c]\n", nd.phls->philo_id, nd.phls->st, nd.phls->mc, nd.phls->sc, nd.phls->nc);
	// 	nd.phls = nd.phls->nxt;
	// 	if (nd.phls->philo_id == id)
	// 		break ;
	// }
	start_the_feast(nd);
}
