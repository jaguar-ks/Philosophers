/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:55:00 by deman_wolf        #+#    #+#             */
/*   Updated: 2023/01/26 17:36:08 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	check_death(t_philo *ph)
{
	int	id;

	id = ph->philo_id;
	while (1)
	{
		if (ph->t_l <= 0)
			return (printf("%d\t%d\tdied\n", ph->ct, ph->philo_id), 1);
		ph = ph->nxt;
		if (ph->philo_id == id)
			break ;
	}
	return (0);
}

void	start_the_feast(t_nd nd)
{
	int	i;
	int	j;
	int	id;

	i = 1;
	j = 1;
	while (1)
	{
		if (nd.inf.h_m_e)
			if (*(nd.inf.h_m_e) == i)
				break ;
		if (!(nd.inf.h_m_e))
			continue ;
		id = nd.phls->philo_id;
		while (nd.phls->philo_id % 2 == j && nd.phls->nxt->philo_id != id)
		{
			pthread_create(&(nd.phls->thrd_id), NULL, &eating, &nd);
			pthread_join(nd.phls->thrd_id, NULL);
			// pthread_create(&(inf.phls->nxt->thrd_id), NULL, &sleeping, &inf);
			// pthread_join(infk.phls->nxt->thrd_id, NULL);
			nd.phls = nd.phls->nxt->nxt;
		}
		if (j == 1)
			j = 0;
		else if (j == 0)
			j = 1;
		if (check_death(nd.phls))
			break ;
		i++;
	}
}
