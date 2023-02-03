/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:53:01 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/03 01:14:11 by faksouss         ###   ########.fr       */
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
	start_the_feast(nd, nd.phls->philo_id);
	del_list(nd.phls, nd.inf.nb_ph);
	if (nd.inf.h_m_e)
		free(nd.inf.h_m_e);
	pthread_mutex_destroy(&nd.inf.prnt);
	pthread_mutex_destroy(&nd.inf.wt);
}
