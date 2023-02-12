/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:55:00 by deman_wolf        #+#    #+#             */
/*   Updated: 2023/02/12 23:50:36 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	out(t_nd nd)
{
	del_list(nd.phls, nd.inf.nb_ph);
	if (nd.inf.h_m_e)
		free(nd.inf.h_m_e);
	free(nd.died);
	pthread_mutex_destroy(&nd.inf.prnt);
	pthread_mutex_destroy(&nd.inf.wt);
	pthread_mutex_destroy(&nd.d);
}

void	*check_death(void *arg)
{
	t_nd	*nd;

	nd = (t_nd *)arg;
	pthread_mutex_lock(&nd->d);
	if (*nd->died == 'd')
		nd->i = 1;
	else
		*nd->died = nd->phls->st;
	pthread_mutex_unlock(&nd->d);
	return (&nd->i);
}

int	check_inf(t_inf in, int ac)
{
	if (in.nb_ph <= 0 || in.t_d < 0 || in.t_e < 0 || in.t_s < 0)
		return (0);
	if (ac == 6 && (!in.h_m_e || *in.h_m_e <= 0))
		return (0);
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

void	init_nd(int ac, char **av, t_nd *nd)
{
	if (ac == 6 || ac == 5)
		nd->inf = init_info(ac, av);
	else
	{
		nd->i = -1;
		return ;
	}
	if (!check_inf(nd->inf, ac))
	{
		nd->i = -2;
		return ;
	}
	nd->phls = setting_up_table(nd->inf);
	nd->died = (char *)malloc(sizeof(char));
	if (!nd->died)
	{
		nd->i = -3;
		return ;
	}
	pthread_mutex_init(&nd->d, NULL);
	nd->i = 0;
}

// void	start_the_feast(t_nd nd, int id)
// {
// 	while (1)
// 	{
// 		while (1)
// 		{
// 			pthread_create(&nd.phls->thrd_id, NULL, &routine, &nd);
// 			usleep(50);
// 			nd.phls = nd.phls->nxt;
// 			if (nd.phls->philo_id == id)
// 				break ;
// 		}
// 		while (1)
// 		{
// 			pthread_join(nd.phls->thrd_id, NULL);
// 			nd.phls = nd.phls->nxt;
// 			if (nd.phls->philo_id == id)
// 				break ;
// 		}
// 		nd.inf.lp += (nd.phls->philo_id == nd.inf.nb_ph);
// 		if ((nd.inf.h_m_e && *nd.inf.h_m_e == nd.inf.lp + 1))
// 			return ;
// 	}
// }
