/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:37:02 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/27 18:19:36 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_philo	*new_node(int id, t_inf inf)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_id = id;
	pthread_mutex_init(&(philo->frk), NULL);
	pthread_mutex_init(&(philo->st_l), NULL);
	philo->t_l = inf.t_d;
	philo->st = 'b';
	philo->ct = 0;
	philo->mc = 0;
	philo->sc = 0;
	if (id % 2 == 0)
		philo->nc = 'e';
	else
		philo->nc = 'o';
	philo->nxt = NULL;
	return (philo);
}

void	add_node_f(t_philo **ph, t_philo *n)
{
	if (ph)
	{
		if (*ph)
			n->nxt = (*ph);
		else
			*ph = n;
		*ph = n;
	}
}

void	del_node(t_philo *philo)
{
	if (pthread_mutex_destroy(&(philo->frk)))
		exit(error(-4));
	// if (pthread_detach(philo->thrd_id))
	// 	exit(error(-3));
	free(philo);
}

void	del_list(t_philo *philo, int id)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp)
	{
		if (philo->philo_id == id)
			philo->nxt = NULL;
		philo = philo->nxt;
		del_node(tmp);
		tmp = philo;
	}
}

t_philo	*last_node(t_philo *tbl)
{
	t_philo	*tmp;

	tmp = tbl;
	while (tmp->nxt)
		tmp = tmp->nxt;
	return (tmp);
}
