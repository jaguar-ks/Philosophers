/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:55:00 by deman_wolf        #+#    #+#             */
/*   Updated: 2023/02/07 02:55:58 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_philo	*setting_up_table(t_inf in)
{
	t_philo	*tbl;
	int		i;

	i = in.nb_ph;
	tbl = NULL;
	while (i > 0)
		add_node_f(&tbl, new_node(i--, in));
	last_node(tbl)->nxt = tbl;
	return (tbl);
}

void	start_the_feast(t_nd nd, int id)
{
	while (1)
	{
		while (1)
		{
			pthread_create(&nd.phls->thrd_id, NULL, &routine, &nd);
			usleep(50);
			nd.phls = nd.phls->nxt;
			if (nd.phls->philo_id == id)
				break ;
		}
		while (1)
		{
			pthread_join(nd.phls->thrd_id, NULL);
			if (nd.phls->st == 'd')
			{
				printf("%lld    %d    died\n", nd.phls->ct, nd.phls->philo_id);
				return ;
			}
			nd.phls = nd.phls->nxt;
			if (nd.phls->philo_id == id)
				break ;
		}
		if ((nd.inf.h_m_e && *nd.inf.h_m_e == nd.inf.lp + 1))
			return ;
		if (nd.phls->philo_id == id)
			nd.inf.lp++;
	}
}
