/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bns.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:34:03 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/22 23:37:41 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BNS_H
# define PHILO_BNS_H

# include<stdlib.h>
# include<sys/time.h>
# include<stdio.h>
# include<string.h>
# include<pthread.h>
# include<unistd.h>
# include<semaphore.h>

typedef struct f_inf
{
	int				nb_ph;
	int				t_d;
	int				t_e;
	int				t_s;
	int				*h_m_e;
}	t_inf;

typedef struct f_philo
{
	pid_t			    prcs_id;
	int					philo_id;
	unsigned long long	ct;
	int					t_l;
	struct f_philo		*nxt;	
}	t_philo;

typedef struct f_nd
{
	struct f_inf	inf;
	struct f_philo	*phls;
    sem_t           *frk;
    sem_t           *prnt;
}	t_nd;

/*initialasing the informations needed*/
t_inf	init_info(int ac, char **av);
/*errors handlling*/
int		error(int er);
/*creating a new node*/
t_philo	*new_node(int id, t_inf in);
/*deleting a node*/
void	del_node(t_philo *philo);
/*deleting a list*/
void	del_list(t_philo *philo, int id);
/*adding node in the begginning of the list*/
void	add_node_f(t_philo **ph, t_philo *n);
/*preparing the table for dinnig*/
t_philo	*setting_up_table(t_inf in);

#endif
