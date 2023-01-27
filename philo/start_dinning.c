/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:55:00 by deman_wolf        #+#    #+#             */
/*   Updated: 2023/01/27 18:20:26 by faksouss         ###   ########.fr       */
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

void	start_the_feast(t_nd nd)
{
	int	i;

	i = 1;
	// while (1)
	// {
		while (1)
		{
			pthread_create(&(nd.phls->thrd_id), NULL, &eating, &nd);
			if (nd.phls->mc && !nd.phls->sc)
				pthread_create(&(nd.phls->thrd_id), NULL, &sleeping, &nd);
			else if (!nd.phls->mc && !nd.phls->sc)
				pthread_create(&(nd.phls->thrd_id), NULL, &thinking, &nd);
			else if (nd.phls->st == 'd')
			{
				wht_the_philo_doing(&nd.inf, nd.phls, 'd');
				break ;
			}
			nd.phls = nd.phls->nxt;
		}
		// if (nd.inf.nb_ph % 2 == 0)
		// 	nd.phls = nd.phls->nxt;
		// id = nd.phls->philo_id;
		// while (nd.phls->philo_id % 2 != j)
		// {
		// 	pthread_create(&(nd.phls->thrd_id), NULL, &sleeping, &nd);
		// 	pthread_join(nd.phls->thrd_id, NULL);
		// 	if (nd.phls->philo_id == id)
		// 		break ;
		// 	nd.phls = nd.phls->nxt->nxt;
		// }
		// if (j == 1)
		// 	j = 0;
		// else if (j == 0)
		// 	j = 1;
	// 	i++;
	// 	if (nd.inf.h_m_e)
	// 		if (*(nd.inf.h_m_e) == i)
	// 			break ;
	// 	if (!(nd.inf.h_m_e))
	// 		continue ;
	// }
}
