/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:55:00 by deman_wolf        #+#    #+#             */
/*   Updated: 2023/02/03 01:14:33 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	nini(t_nd nd)
{
	if (nd.phls->philo_id % 2 == 1)
		usleep(nd.inf.t_d);
	if (nd.phls->philo_id % 2 == 0)
		usleep(nd.inf.t_d * 4);
	if (nd.phls->philo_id == nd.inf.nb_ph && nd.inf.nb_ph % 2 != 0)
		usleep(nd.inf.t_d * 6);
}

void	start_the_feast(t_nd nd, int id)
{
	while (1)
	{
		while (1)
		{
			pthread_create(&nd.phls->thrd_id, NULL, &routine, &nd);
			nini(nd);
			nd.phls = nd.phls->nxt;
			if (nd.phls->philo_id == id)
				break ;
		}
		while (1)
		{
			pthread_join(nd.phls->thrd_id, NULL);
			if (nd.phls->nxt->philo_id == id || nd.phls->st == 'd')
				break ;
			nd.phls = nd.phls->nxt;
		}
		if ((nd.inf.h_m_e && *nd.inf.h_m_e == nd.inf.lp + 1)
			|| nd.phls->st == 'd')
			break ;
		nd.phls = nd.phls->nxt;
		if (nd.phls->philo_id == id)
			nd.inf.lp++;
	}
}
