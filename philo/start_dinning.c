/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:55:00 by deman_wolf        #+#    #+#             */
/*   Updated: 2023/01/30 20:16:37 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	check_death(t_nd nd)
{
	int	id;

	id = nd.phls->philo_id;
	while (1)
	{
		if (nd.phls->t_l < nd.inf.t_e || nd.phls->t_l < nd.inf.t_s)
		{
			nd.phls->st = 'd';
			return (1);
		}
		nd.phls = nd.phls->nxt;
		if (nd.phls->philo_id == id)
			break ;
	}
	return (0);
}

int	odd_philo(t_nd nd)
{
	int			id;
	pthread_t	tc;

	id = nd.phls->philo_id;
	while (nd.phls->philo_id % 2 != 0)
	{
		pthread_mutex_lock(&nd.inf.wrt);
		pthread_mutex_lock(&nd.inf.st_l);
		if (!nd.phls->mc)
		{
			pthread_create(&nd.phls->thrd_id, NULL, &eating, &nd);
			if (nd.phls->st == 't' || nd.phls->st == 'w')
				pthread_create(&tc, NULL, &thinking, &nd);
		}
		if (nd.phls->mc)
			pthread_create(&nd.phls->thrd_id, NULL, &sleeping, &nd);
		if (nd.phls->st == 'd')
			return (1);
		pthread_mutex_unlock(&nd.inf.wrt);
		pthread_mutex_unlock(&nd.inf.st_l);
		nd.phls = nd.phls->nxt->nxt;
		if (nd.phls->philo_id == id)
			break ;
	}
	return (0);
}

int	even_philo(t_nd nd)
{
	int			id;
	pthread_t	tc;

	nd.phls = nd.phls->nxt;
	id = nd.phls->philo_id;
	while (nd.phls->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&nd.inf.wrt);
		pthread_mutex_lock(&nd.inf.st_l);
		if (!nd.phls->mc)
		{
			pthread_create(&nd.phls->thrd_id, NULL, &eating, &nd);
			if (nd.phls->st == 't' || nd.phls->st == 'w')
				pthread_create(&tc, NULL, &thinking, &nd);
		}
		if (nd.phls->mc)
			pthread_create(&nd.phls->thrd_id, NULL, &sleeping, &nd);
		if (nd.phls->st == 'd')
			return (1);
		pthread_mutex_unlock(&nd.inf.wrt);
		pthread_mutex_unlock(&nd.inf.st_l);
		nd.phls = nd.phls->nxt->nxt;
		if (nd.phls->philo_id == id)
			break ;
	}
	return (0);
}

void	start_the_feast(t_nd nd)
{
	t_philo	*hd;

	hd = nd.phls;
	while (1)
	{
		if (nd.inf.h_m_e && *nd.inf.h_m_e == nd.inf.lp)
			break ;
		if (odd_philo(nd))
			break ;
		usleep(100);
		// if (even_philo(nd))
		// 	break ;
		nd.phls = hd;
		nd.inf.lp++;
	}
}

// void	start_the_feast(t_nd nd)
// {
// 	int	i;

// 	i = 1;
// 	while (1)
// 	{
// 		if (nd.phls->st == 'd')
// 			break ;
// 		if (nd.phls->nc == 'o')
// 		{
// 			pthread_create(&(nd.phls->thrd_id), NULL, &eating, &nd);
// 			nd.phls->nc = 'e';
// 		}
// 		else if (nd.phls->nc == 'e')
// 		{
// 			nd.phls->st = 'w';
// 			pthread_create(&(nd.phls->thrd_id), NULL, &thinking, &nd);
// 			nd.phls->nc = 'o';
// 		}
// 		if (nd.phls->st == 'e' && !nd.phls->sc)
// 			pthread_create(&(nd.phls->thrd_id), NULL, &sleeping, &nd);
// 		nd.phls = nd.phls->nxt;
// 		// while (1)
// 		// {
// 		// 	if (!nd.phls->mc && !nd.phls->sc)
// 		// 	if (nd.phls->st == 'd')
// 		// 	{
// 		// 		wht_the_philo_doing(&nd.inf, nd.phls, 'd');
// 		// 		break ;
// 		// 	}
// 		// 	nd.phls = nd.phls->nxt;
// 		// }
// 		// if (nd.inf.nb_ph % 2 == 0)
// 		// 	nd.phls = nd.phls->nxt;
// 		// id = nd.phls->philo_id;
// 		// while (nd.phls->philo_id % 2 != j)
// 		// {
// 		// 	pthread_create(&(nd.phls->thrd_id), NULL, &sleeping, &nd);
// 		// 	pthread_join(nd.phls->thrd_id, NULL);
// 		// 	if (nd.phls->philo_id == id)
// 		// 		break ;
// 		// 	nd.phls = nd.phls->nxt->nxt;
// 		// }
// 		// if (j == 1)
// 		// 	j = 0;
// 		// else if (j == 0)
// 		// 	j = 1;
// 		// i++;
// 		// if (nd.inf.h_m_e)
// 		// 	if (*(nd.inf.h_m_e) == i)
// 		// 		break ;
// 		// if (!(nd.inf.h_m_e))
// 		// 	continue ;
// 	}
// 	wht_the_philo_doing(&nd.inf, nd.phls, nd.phls->st);
// }
