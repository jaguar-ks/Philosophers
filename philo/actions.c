/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:06:02 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/04 23:52:07 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	check_death(t_nd nd)
{
	static char	t;

	if (t == 'd')
		return (1);
	t = nd.phls->st;
	return (0);
}

void	out(t_nd nd)
{
	del_list(nd.phls, nd.phls->philo_id);
	if (nd.inf.h_m_e)
		free(nd.inf.h_m_e);
	pthread_mutex_destroy(&nd.inf.prnt);
	pthread_mutex_destroy(&nd.inf.wt);
}

void	*wht_the_philo_doing(void *arg)
{
	t_nd		nd;

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

void	*print_state(t_nd nd)
{
	if (check_death(nd))
		return (NULL);
	pthread_mutex_lock(&nd.inf.wt);
	if (nd.phls->st == 'd')
		nd.phls->ct += nd.phls->t_l;
	if (nd.phls->st == 'e')
	{
		pthread_mutex_unlock(&nd.phls->f);
		if (nd.phls != nd.phls->nxt)
			pthread_mutex_unlock(&nd.phls->nxt->f);
	}
	pthread_create(&nd.inf.wrtr, NULL, &wht_the_philo_doing, &nd);
	pthread_join(nd.inf.wrtr, NULL);
	pthread_mutex_unlock(&nd.inf.wt);
	return (NULL);
}

void	*routine(void *arg)
{
	t_nd	nd;

	nd = *(t_nd *)arg;
	if (check_death(nd))
		return (NULL);
	pthread_mutex_lock(&nd.phls->f);
	if (nd.phls != nd.phls->nxt)
		pthread_mutex_lock(&nd.phls->nxt->f);
	nd.phls->st = 'f';
	print_state(nd);
	if (nd.phls->t_l < nd.inf.t_e || nd.phls == nd.phls->nxt)
		return (nd.phls->st = 'd', print_state(nd));
	nd.phls->st = 'e';
	print_state(nd);
	nd.phls->ct += nd.inf.t_e;
	nd.phls->t_l = nd.inf.t_d;
	nd.phls->st = 's';
	print_state(nd);
	if (nd.phls->t_l < nd.inf.t_s)
		return (nd.phls->st = 'd', print_state(nd));
	nd.phls->ct += nd.inf.t_s;
	nd.phls->t_l -= nd.inf.t_s;
	nd.phls->st = 't';
	print_state(nd);
	return (NULL);
}
