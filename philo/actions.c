/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:06:02 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/31 16:35:37 by deman_wolf       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	wht_the_philo_doing(t_philo *ph, char c)
{
	if (c == 't' || c == 's' || c == 'd' || c == 'f' || c == 'e')
	{
		printf("%lld\t", ph->ct);
		printf("%d\t", ph->philo_id);
	}
	if (c == 't')
		printf("is thinking\n");
	else if (c == 's')
		printf("is sleeping\n");
	else if (c == 'd')
		printf("died\n");
	else if (c == 'f')
		printf("has taken a fork\n");
	else if (c == 'e')
	{
		printf("has taken a fork\n");
		printf("%lld\t", ph->ct);
		printf("%d\t", ph->philo_id);
		printf("is eating\n");
	}
}

void	*routine(void *arg)
{
	t_nd	nd;
	int		cd;
	
	nd = *(t_nd *)arg;
	if (nd.phls->t_l - nd.inf.t_e < 0 || !nd.phls->nxt)
		return (nd.phls->st = 'd', NULL);
	wht_the_philo_doing(nd.phls, 'f');
	wht_the_philo_doing(nd.phls, 'e');
	nd.phls->ct += nd.inf.t_e;
	nd.phls->t_l = nd.inf.t_d;
	cd = 1;
	if (((nd.phls->philo_id % 2 == 0) && (nd.phls->nxt->philo_id == nd.inf.nb_ph))
		|| (nd.phls->nxt->philo_id % 2 == 0) || nd.phls->philo_id == nd.inf.nb_ph)
	{
		if ((nd.phls->philo_id % 2 == 0) && (nd.phls->nxt->philo_id == nd.inf.nb_ph))
			cd = 2;
		nd.phls->nxt->ct += nd.inf.t_e * cd;
		nd.phls->nxt->t_l -= nd.inf.t_e * cd;
	}
	wht_the_philo_doing(nd.phls, 's');
	nd.phls->ct += nd.inf.t_s;
	nd.phls->t_l -= nd.inf.t_s;
	wht_the_philo_doing(nd.phls, 't');
	return (NULL);
}
