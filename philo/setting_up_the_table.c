/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_up_the_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:35:30 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/24 20:13:33 by deman_wolf       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_philo	*setting_up_table(t_inf in)
{
	t_philo	*tbl;
	int		i;

	i = in.nb_ph;
	tbl = NULL;
	while (--i >= 0)
		add_node_f(&tbl, new_node(i + 1));
	last_node(tbl)->nxt = tbl;
	return (tbl);
}
