/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:50:01 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/31 16:36:49 by deman_wolf       ###   ########.fr       */
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
	int	nb_ph;
	int	t_d;
	int	t_e;
	int	t_s;
	int	*h_m_e;
	int	lp;
}	t_inf;

typedef struct f_philo
{
	pthread_t			thrd_id;
	int					philo_id;
	unsigned long long	ct;
	int					t_l;
	int					st;
	struct f_philo		*nxt;	
}	t_philo;

typedef struct f_nd
{
	struct f_inf	inf;
	struct f_philo	*phls;
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
/*taking the last node*/
t_philo	*last_node(t_philo *tbl);
/*print the state of philosopher*/
void	wht_the_philo_doing(t_philo *ph, char c);
/*Sumilation*/
void	start_the_feast(t_nd inf);
/*routine*/
void	*routine(void *arg);

#endif
