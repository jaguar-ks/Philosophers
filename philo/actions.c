/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:06:02 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/03 01:09:38 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	*wht_the_philo_doing(void *arg)
{
	t_nd	nd;

	nd = *(t_nd *)arg;
	pthread_mutex_lock(&nd.inf.prnt);
	printf("%lld    ", nd.phls->ct);
	printf("%d    ", nd.phls->philo_id);
	if (nd.phls->st == 't')
		printf("is thinking\n");
	else if (nd.phls->st == 's')
		printf("is sleeping\n");
	else if (nd.phls->st == 'd')
		printf("died\n");
	else if (nd.phls->st == 'f')
		printf("has taken a fork\n");
	else if (nd.phls->st == 'e')
	{
		printf("has taken a fork\n");
		printf("%lld    ", nd.phls->ct);
		printf("%d    ", nd.phls->philo_id);
		printf("is eating\n");
	}
	pthread_mutex_unlock(&nd.inf.prnt);
	return (NULL);
}

void	print_state(t_nd nd)
{
	if (nd.phls->st == 'd')
		nd.phls->ct += nd.phls->t_l;
	pthread_create(&nd.inf.wrtr, NULL, &wht_the_philo_doing, &nd);
	pthread_join(nd.inf.wrtr, NULL);
}

void	*routine(void *arg)
{
	t_nd	nd;

	nd = *(t_nd *)arg;
	pthread_mutex_lock(&nd.inf.wt);
	pthread_mutex_lock(&nd.phls->f);
	nd.phls->st = 'f';
	print_state(nd);
	if (nd.phls->t_l < nd.inf.t_e || nd.phls == nd.phls->nxt)
		return (nd.phls->st = 'd', print_state(nd), NULL);
	pthread_mutex_lock(&nd.phls->nxt->f);
	nd.phls->st = 'e';
	print_state(nd);
	nd.phls->ct += nd.inf.t_e;
	nd.phls->t_l = nd.inf.t_d;
	pthread_mutex_unlock(&nd.phls->f);
	pthread_mutex_unlock(&nd.phls->nxt->f);
	nd.phls->st = 's';
	print_state(nd);
	nd.phls->ct += nd.inf.t_s;
	nd.phls->t_l -= nd.inf.t_s;
	nd.phls->st = 't';
	print_state(nd);
	pthread_mutex_unlock(&nd.inf.wt);
	return (NULL);
}
