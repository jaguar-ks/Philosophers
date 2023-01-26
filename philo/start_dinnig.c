/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinnig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:55:00 by deman_wolf        #+#    #+#             */
/*   Updated: 2023/01/25 16:04:31 by deman_wolf       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	*eat(void *ph)
{
	t_philo *phl;
	t_inf	*inf;

	inf = (t_inf *)ph;
	phl = inf->phls;
	if ()
	pthread_mutex_lock(&phl->frk);
	pthread_mutex_lock(&phl->nxt->frk);
	printf("%d\t%d has taken a fork\n", inf->ct, phl->philo_id);
	printf("%d\t%d has taken a fork\n", inf->ct, phl->philo_id);
}

void	start_the_feast(t_inf inf, t_philo *phls)
{
	while (1)
	{
		pthread_create(&phls->thrd_id, NULL, eat, &inf);
	}
}
