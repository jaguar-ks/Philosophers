/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:06:02 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/30 20:15:58 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	wht_the_philo_doing(t_philo *ph, char c)
{
	// printf("time left to die>>[%d]\n", ph->t_l);
	if (c == 't' || c == 's' || c == 'd' || c == 'f' || c == 'e')
	{
		printf("%d\t", ph->ct);
		printf("%d\t", ph->philo_id);
	}
	if (c == 't')
		printf("is thinking\n");
	else if (c == 's')
		printf("is sleeping\n");
	else if (c == 'd')
		printf("died\n");
	else if (c == 'f')
		printf("has taken a fork of philo[%d]\n", ph->philo_id);
	// else if (c == 'w')
	// 	printf("is waiting\n");
	else if (c == 'e')
	{
		printf("has taken a fork of philo[%d]\n", ph->nxt->philo_id);
		printf("%d\t", ph->ct);
		printf("%d\t", ph->philo_id);
		printf("is eating\n");
	}
}

void	*eating(void *arg)
{
	t_nd	in;
	int		i;

	in = *(t_nd *)arg;
	if (in.phls->mc == 1 && in.phls->st != 'd')
		return (NULL);
	i = 0;
	pthread_mutex_lock(&(in.phls->frk));
	in.phls->st = 'f';
	wht_the_philo_doing(in.phls, in.phls->st);
	in.phls->st = 'w';
	pthread_mutex_lock(&(in.phls->nxt->frk));
	if (in.phls->st == 'd')
		return (NULL);
	in.phls->st = 'e';
	wht_the_philo_doing(in.phls, in.phls->st);
	while (i < in.inf.t_e)
	{
		if (in.phls->t_l - i <= 0)
		{
			in.phls->st = 'd';
			wht_the_philo_doing(in.phls, 'd');
			break ;
		}
		else
			in.phls->t_l -= 1;
		in.phls->ct += 1;
		i++;
	}
	in.phls->t_l = in.inf.t_d;
	in.phls->mc = 1;
	pthread_mutex_unlock(&(in.phls->frk));
	pthread_mutex_unlock(&(in.phls->nxt->frk));
	return (NULL);
}

void	*sleeping(void *arg)
{
	t_nd	in;
	int		i;

	in = *(t_nd *)arg;
	if (in.phls->mc == 0 && in.phls->st != 'd')
		return (NULL);
	i = 0;
	in.phls->st = 's';
	wht_the_philo_doing(in.phls, in.phls->st);
	while (i < in.inf.t_s)
	{
		if (in.phls->t_l <= 0)
		{
			wht_the_philo_doing(in.phls, 'd');
			in.phls->st = 'd';
			break ;
		}
		in.phls->t_l -= 1;
		in.phls->ct += 1;
		i++;
	}
	in.phls->st = 't';
	in.phls->mc = 0;
	return (NULL);
}

void	*thinking(void *arg)
{
	t_nd	in;

	in = *(t_nd *)arg;
	if (in.phls->st == 't')
		wht_the_philo_doing(in.phls, in.phls->st);
	while (in.phls->st == 'w' || in.phls->st == 't')
	{
		in.phls->t_l -= 1;
		in.phls->ct += 1;
		if (in.phls->t_l <= 0)
		{
			wht_the_philo_doing(in.phls, 'd');
			in.phls->st = 'd';
			break ;
		}
	}
	return (NULL);
}
