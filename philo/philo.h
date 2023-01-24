/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:50:01 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/24 17:34:49 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdlib.h>
# include<sys/time.h>
# include<stdio.h>
# include<string.h>
# include<pthread.h>
# include<unistd.h>

typedef struct f_inf
{
	long	nb_ph;
	long	t_d;
	long	t_e;
	long	t_s;
	long	*h_m_e;
}	t_inf;

typedef struct f_philo
{
	pthread_t		thrd_id;
	int				philo_id;
	pthread_mutex_t	frk;
	pthread_mutex_t	wrt;
	struct f_philo	*nxt;	
}	t_philo;

/*initialasing the informations needed*/
t_inf	init_info(int ac, char **av);
/*errors handlling*/
int		error(int er);

#endif
