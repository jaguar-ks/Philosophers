/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_bns_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:37:02 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/22 23:37:39 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bns.h"

t_philo	*new_node(int id, t_inf inf)
{
	t_philo	*philo;
	int		cd;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	cd = 0;
	if (id % 2 == 0)
		cd = 1;
	else if (inf.nb_ph % 2 == 1 && id == inf.nb_ph && inf.nb_ph > 1)
		cd = 2;
	philo->philo_id = id;
	philo->t_l = inf.t_d / (cd + 1);
	philo->ct = inf.t_e * cd;
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

void	del_list(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (philo)
	{
		free(tmp);
		philo = philo->nxt;
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

t_philo	*setting_up_table(t_inf in)
{
	t_philo	*tbl;
	int		i;

	i = in.nb_ph;
	tbl = NULL;
	while (i > 0)
		add_node_f(&tbl, new_node(i--, in));
	return (tbl);
}
