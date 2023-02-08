/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:06:02 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/08 03:30:51 by deman_wolf       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	out(t_nd nd)
{
	del_list(nd.phls, nd.inf.nb_ph);
	if (nd.inf.h_m_e)
		free(nd.inf.h_m_e);
	free(nd.died);
	pthread_mutex_destroy(&nd.inf.prnt);
	pthread_mutex_destroy(&nd.inf.wt);
}

void	*wht_the_philo_doing(void *arg)
{
	t_nd		nd;

	nd = *(t_nd *)arg;
	pthread_mutex_lock(&nd.inf.prnt);
	if (*nd.died == 'd')
		return (pthread_mutex_unlock(&nd.inf.prnt), NULL);
	*nd.died = nd.phls->st;
	if (nd.phls->st == 'd')
		printf("%lld    %d    died\n", nd.phls->ct + nd.phls->t_l,
			nd.phls->philo_id);
	if (nd.phls->st == 't')
		printf("%lld    %d    is thinking\n", nd.phls->ct, nd.phls->philo_id);
	if (nd.phls->st == 's')
		printf("%lld    %d    is sleeping\n", nd.phls->ct, nd.phls->philo_id);
	if (nd.phls->st == 'f' || nd.phls->st == 'e')
		printf("%lld    %d    has taken a fork\n", nd.phls->ct,
			nd.phls->philo_id);
	if (nd.phls->st == 'e')
		printf("%lld    %d    is eating\n", nd.phls->ct, nd.phls->philo_id);
	usleep(50);
	pthread_mutex_unlock(&nd.inf.prnt);
	return (NULL);
}

void	print_state(t_nd nd)
{
	pthread_mutex_lock(&nd.inf.wt);
	if (nd.phls->st == 'e')
	{
		pthread_mutex_unlock(&nd.phls->f);
		if (nd.phls != nd.phls->nxt)
			pthread_mutex_unlock(&nd.phls->nxt->f);
	}
	pthread_create(&nd.inf.wrtr, NULL, &wht_the_philo_doing, &nd);
	pthread_join(nd.inf.wrtr, NULL);
	pthread_mutex_unlock(&nd.inf.wt);
}

void	*routine(void *arg)
{
	t_nd	nd;

	nd = *(t_nd *)arg;
	pthread_mutex_lock(&nd.phls->f);
	if (nd.phls != nd.phls->nxt)
		pthread_mutex_lock(&nd.phls->nxt->f);
	nd.phls->st = 'f';
	print_state(nd);
	if (nd.phls->t_l < nd.inf.t_e || nd.phls == nd.phls->nxt)
		return (nd.phls->st = 'd', print_state(nd), NULL);
	nd.phls->st = 'e';
	print_state(nd);
	nd.phls->ct += nd.inf.t_e;
	nd.phls->t_l = nd.inf.t_d;
	nd.phls->st = 's';
	print_state(nd);
	if (nd.phls->t_l < nd.inf.t_s)
		return (nd.phls->st = 'd', print_state(nd), NULL);
	nd.phls->ct += nd.inf.t_s;
	nd.phls->t_l -= nd.inf.t_s;
	nd.phls->st = 't';
	print_state(nd);
	return (NULL);
}
