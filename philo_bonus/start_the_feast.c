/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_the_feast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:28:22 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/22 23:37:45 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bns.h"

void	out(t_nd nd)
{
	del_list(nd.phls);
	if (nd.inf.h_m_e)
		free(nd.inf.h_m_e);
    sem_close(nd.frk);
    sem_close(nd.prnt);
    sem_unlink("fork");
    sem_unlink("print");
    exit(0);
}

void    routine(t_nd nd, t_philo *phl)
{
    int lp = 0;
    while (1)
    {
        sem_wait(nd.frk);
        if (nd.inf.nb_ph > 1)
            sem_wait(nd.prnt);
        printf("%lld    %d    has taken a fork\n", phl->ct, phl->philo_id);
        if (phl->t_l < nd.inf.t_e || nd.inf.nb_ph == 1)
        {
            printf("%lld    %d    died\n", phl->ct + phl->t_l, phl->philo_id);
            exit(1);
        }
        sem_post(nd.prnt);
        sem_wait(nd.frk);
        sem_wait(nd.prnt);
        printf("%lld    %d    has taken a fork\n", phl->ct, phl->philo_id);
        printf("%lld    %d    is eating\n", phl->ct, phl->philo_id);
        sem_post(nd.prnt);
        sem_post(nd.frk);
        sem_post(nd.frk);
        phl->ct += nd.inf.t_e;
        phl->t_l = nd.inf.t_d;
        sem_wait(nd.prnt);
        printf("%lld    %d    is sleeping\n", phl->ct, phl->philo_id);
        if (phl->t_l < nd.inf.t_s)
        {
            printf("%lld    %d    died\n", phl->ct + phl->t_l, phl->philo_id);
            exit(1);
        }
        sem_post(nd.prnt);
        phl->ct += nd.inf.t_s;
        phl->t_l -= nd.inf.t_s;
        sem_wait(nd.prnt);
        printf("%lld    %d    is thinking\n", phl->ct, phl->philo_id);
        sem_post(nd.prnt);
        if (nd.inf.h_m_e && lp == *nd.inf.h_m_e)
            exit(0);
        lp++;
    }
}

void    start_the_feast(t_nd nd)
{
    t_philo *tmp;

    tmp = nd.phls;
    while (tmp)
    {
        tmp->prcs_id = fork();
        tmp = tmp->nxt;
    }
    tmp = nd.phls;
    while (tmp)
    {
        if (!tmp->prcs_id)
            routine(nd, tmp);
        tmp = tmp->nxt;
    }
    tmp = nd.phls;
    while (tmp)
    {
        waitpid(tmp->prcs_id, NULL, 0);
        tmp = tmp->nxt;
    }
}
