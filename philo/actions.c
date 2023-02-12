/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:06:02 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/12 23:53:49 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	pick_forks(t_nd nd)
{
	pthread_mutex_lock(&nd.phls->f);
	if (nd.phls != nd.phls->nxt)
		pthread_mutex_lock(&nd.phls->nxt->f);
	printf("%lld    %d    has taken a fork\n", nd.phls->ct, nd.phls->philo_id);
}

void	put_forks(t_nd nd)
{
	pthread_mutex_unlock(&nd.phls->f);
	if (nd.phls != nd.phls->nxt)
		pthread_mutex_unlock(&nd.phls->nxt->f);
	if (nd.phls->st == 'e')
	{
		printf("%lld    %d    has taken a fork\n", nd.phls->ct,
			nd.phls->philo_id);
		printf("%lld    %d    is eating\n", nd.phls->ct, nd.phls->philo_id);
		nd.phls->ct += nd.inf.t_e;
		nd.phls->t_l = nd.inf.t_d;
	}
	else if (nd.phls->st == 'd')
		printf("%lld    %d    died\n", nd.phls->ct + nd.phls->t_l,
			nd.phls->philo_id);
}

// void	*wht_the_philo_doing(void *arg)
// {
// 	t_nd		nd;

// 	nd = *(t_nd *)arg;
// 	// if (check_death(nd))
// 	// 	return (NULL);
// 	pthread_mutex_lock(&nd.inf.prnt);
// 	// printf("prnt >> [%p]\n", &nd.inf.prnt);
// 	if (nd.phls->st == 'd')
// 		printf("%lld    %d    died\n", nd.phls->ct + nd.phls->t_l,
// 			nd.phls->philo_id);
// 	if (nd.phls->st == 't')
// 	if (nd.phls->st == 's')
// 	if (nd.phls->st == 'f' || nd.phls->st == 'e')
// 		printf("%lld    %d    has taken a fork\n", nd.phls->ct,
// 			nd.phls->philo_id);
// 	if (nd.phls->st == 'e')	
// 	pthread_mutex_unlock(&nd.inf.prnt);
// 	return (NULL);
// }

// void	print_state(t_nd nd)
// {
// 	pthread_mutex_lock(&nd.inf.wt);
// 	// printf("wt >> [%p]\n", &nd.inf.wt);
// 	if (nd.phls->st == 'd')
// 		put_forks(nd);
// 	pthread_create(&nd.inf.wrtr, NULL, &wht_the_philo_doing, &nd);
// 	pthread_join(nd.inf.wrtr, NULL);
// 	if (nd.phls->st == 'e')
// 		put_forks(nd);
// 	pthread_mutex_unlock(&nd.inf.wt);
// }

int	print_state(t_nd nd)
{
	int	*ch;

	pthread_mutex_lock(&nd.inf.wt);
	pthread_create(&nd.angl_of_dth, NULL, &check_death, &nd);
	usleep(50);
	pthread_join(nd.angl_of_dth, (void *)&ch);
	if (*ch == 1)
		return (pthread_mutex_unlock(&nd.inf.wt), 1);
	if (nd.phls->st == 'f')
		pick_forks(nd);
	else if (nd.phls->st == 'd' || nd.phls->st == 'e')
		put_forks(nd);
	else if (nd.phls->st == 's')
	{
		printf("%lld    %d    is sleeping\n", nd.phls->ct, nd.phls->philo_id);
		nd.phls->ct += nd.inf.t_s;
		nd.phls->t_l -= nd.inf.t_s;
	}
	else if (nd.phls->st == 't')
		printf("%lld    %d    is thinking\n", nd.phls->ct, nd.phls->philo_id);
	pthread_mutex_unlock(&nd.inf.wt);
	return (0);
}

void	*routine(void *arg)
{
	t_nd	nd;

	nd = *(t_nd *)arg;
	pthread_mutex_lock(&nd.inf.prnt);
	nd.phls->st = 'f';
	if (print_state(nd))
		return (pthread_mutex_unlock(&nd.inf.prnt), NULL);
	if (nd.phls->t_l < nd.inf.t_e || nd.phls == nd.phls->nxt)
		nd.phls->st = 'd';
	else
		nd.phls->st = 'e';
	if (print_state(nd))
		return (pthread_mutex_unlock(&nd.inf.prnt), NULL);
	nd.phls->st = 's';
	if (print_state(nd))
		return (pthread_mutex_unlock(&nd.inf.prnt), NULL);
	if (nd.phls->t_l + nd.inf.t_s < nd.inf.t_s)
	{
		nd.phls->ct -= nd.inf.t_s;
		nd.phls->t_l += nd.inf.t_s;
		nd.phls->st = 'd';
	}
	else
		nd.phls->st = 't';
	return (pthread_mutex_unlock(&nd.inf.prnt), NULL);
}
