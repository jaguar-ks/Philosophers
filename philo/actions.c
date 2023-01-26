/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:06:02 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/26 17:37:36 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	wht_the_philo_doing(t_inf *inf, t_philo *ph, char *act)
{
	printf("[%d]\n", inf->phls->philo_id);
	pthread_mutex_lock(&(inf->wrt));
	printf("%d\t", ph->ct);
	printf("%d\t", ph->philo_id);
	printf("%s\n", act);
	pthread_mutex_unlock(&(inf->wrt));
}

void	*eating(void *arg)
{
	t_nd	in;

	in = *(t_nd *)arg;
	printf("[%d]\n", in.phls->philo_id);
	pthread_mutex_lock(&(in.phls->frk));
	wht_the_philo_doing(&in.inf, in.phls, "has taken a fork");
	pthread_mutex_lock(&(in.phls->nxt->frk));
	wht_the_philo_doing(&in.inf, in.phls, "has taken a fork");
	in.phls->t_l = in.inf.t_d;
	wht_the_philo_doing(&in.inf, in.phls, "is eating");
	in.phls->ct += in.inf.t_e;
	pthread_mutex_unlock(&(in.phls->nxt->frk));
	pthread_mutex_unlock(&(in.phls->frk));
	return (NULL);
}

void	*sleeping(void *arg)
{
	t_nd	in;

	in = *(t_nd *)arg;
	wht_the_philo_doing(&in.inf, in.phls, "is sleeping");
	in.phls->ct += in.inf.t_s;
	in.phls->t_l -= in.inf.t_s;
	wht_the_philo_doing(&in.inf, in.phls, "is thinking");
	return (NULL);
}
