/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:55:00 by deman_wolf        #+#    #+#             */
/*   Updated: 2023/01/31 16:29:24 by deman_wolf       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	start_the_feast(t_nd nd)
{
	t_philo	*hd;

	hd = nd.phls;
	while (1)
	{
		pthread_create(&nd.phls->thrd_id, NULL, &routine, &nd);
		pthread_join(nd.phls->thrd_id, NULL);
		if (nd.phls->st == 'd')
		{
			nd.phls->ct += nd.phls->t_l;
			wht_the_philo_doing(nd.phls, 'd');
			break ;
		}
		if (nd.inf.h_m_e && *nd.inf.h_m_e == nd.inf.lp)
			break ;
		nd.phls = nd.phls->nxt;
		if (nd.phls->nxt == hd)
			nd.inf.lp++;
	}
}
