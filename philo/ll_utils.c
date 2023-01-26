/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:37:02 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/25 15:51:11 by deman_wolf       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_philo	*new_node(int id)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_id = id;
	if (pthread_mutex_init(&philo->frk, NULL))
		return (free(philo), NULL);
	philo->t_l = 0;
	philo->t_s = 0;
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
	if (pthread_mutex_destroy(&philo->frk))
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
