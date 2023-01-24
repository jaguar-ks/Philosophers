/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:37:02 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/24 20:12:35 by deman_wolf       ###   ########.fr       */
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
	if (pthread_mutex_init(&philo->wrt, NULL))
		return (pthread_mutex_destroy(&philo->frk), free(philo), NULL);
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
	if (pthread_detach(philo->thrd_id))
		exit(error(-3));
	if (pthread_mutex_destroy(&philo->frk)
		|| pthread_mutex_destroy(&philo->wrt))
		exit(error(-4));
	free(philo);
}

void	del_list(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (philo)
	{
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
