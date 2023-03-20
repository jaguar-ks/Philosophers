/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:55:00 by deman_wolf        #+#    #+#             */
/*   Updated: 2023/03/20 01:46:37 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	error(int er)
{
	if (er == -1)
		write(2, "Error: Invalid number of arguments\n", 36);
	if (er == -2)
		write(2, "Error: Wrong value of some arguments\n", 38);
	return (1);
}

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
		while (!nd.died)
		{
			pthread_create(&nd.phls->thrd_id, NULL, &routine, &nd);
			usleep(80);
			nd.phls = nd.phls->nxt;
			if (nd.phls->philo_id == id)
				break ;
		}
		while (1)
		{
			pthread_join(nd.phls->thrd_id, (void *)&nd.wait);
			if (nd.wait)
				return ((void)printf("%lld    %d    died\n", nd.phls->ct
						+ nd.phls->t_l, nd.phls->philo_id));
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
