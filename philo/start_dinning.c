/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:55:00 by deman_wolf        #+#    #+#             */
/*   Updated: 2023/02/03 23:08:21 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

// void	nini(t_nd nd, int id)
// {
// 	if (id == nd.inf.nb_ph && nd.inf.nb_ph % 2 != 0)
// 		usleep(600 * 5);
// 	else if (id % 2 == 0)
// 		usleep(600 * 3);
// 	else if (id % 2 != 0)
// 		usleep(600);
// }

void	start_the_feast(t_nd nd, int id)
{
	while (1)
	{
		while (1)
		{
			pthread_create(&nd.phls->thrd_id, NULL, &routine, &nd);
			usleep(100);
			nd.phls = nd.phls->nxt;
			if (nd.phls->philo_id == id)
				break ;
		}
		while (1)
		{
			pthread_join(nd.phls->thrd_id, NULL);
			usleep(100);
			nd.phls = nd.phls->nxt;
			if (nd.phls->philo_id == id)
				break ;
		}
		if ((nd.inf.h_m_e && *nd.inf.h_m_e == nd.inf.lp + 1))
			out(nd);
		if (nd.phls->philo_id == id)
			nd.inf.lp++;
	}
}
