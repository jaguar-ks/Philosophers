/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:50:01 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/26 17:35:23 by faksouss         ###   ########.fr       */
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
	long			nb_ph;
	long			t_d;
	long			t_e;
	long			t_s;
	long			*h_m_e;
	pthread_mutex_t	wrt;
	struct f_philo	*phls;
}	t_inf;

typedef struct f_philo
{
	pthread_t		thrd_id;
	int				philo_id;
	int				ct;
	int				t_l;
	int				t_s;
	pthread_mutex_t	frk;
	struct f_philo	*nxt;	
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
t_philo	*new_node(int id);
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
/*eating*/
void	*eating(void *arg);
/*sleeping*/
void	*sleeping(void *arg);
/*print the state of philosopher*/
void	wht_the_philo_doing(t_inf *inf, t_philo *ph, char *act);
/*Sumilation*/
void	start_the_feast(t_nd inf);


#endif
