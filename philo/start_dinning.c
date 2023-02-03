/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:55:00 by deman_wolf        #+#    #+#             */
/*   Updated: 2023/02/03 16:49:52 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	nini(t_nd nd)
{
	if (nd.phls->philo_id == nd.inf.nb_ph && nd.inf.nb_ph % 2 != 0)
		usleep(nd.inf.t_e * 3);
	else
		usleep(nd.inf.t_e * ((nd.phls->philo_id % 2 == 0) + 1));
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
			nd.phls = nd.phls->nxt;
			if (nd.phls->philo_id == id)
				break ;
		}
		if (nd.inf.h_m_e && *nd.inf.h_m_e == nd.inf.lp + 1)
			break ;
		if (nd.phls->philo_id == id)
			nd.inf.lp++;
	}
}
