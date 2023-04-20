/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:50:01 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/20 13:07:05 by faksouss         ###   ########.fr       */
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
	int				nb_ph;
	int				t_d;
	int				t_e;
	int				t_s;
	int				*h_m_e;
	int				lp;
	pthread_mutex_t	prnt;
	pthread_t		wrtr;
	pthread_mutex_t	wt;
}	t_inf;

typedef struct f_philo
{
	pthread_t			thrd_id;
	int					philo_id;
	unsigned long long	ct;
	int					t_l;
	int					st;
	pthread_mutex_t		f;
	struct f_philo		*nxt;	
}	t_philo;

typedef struct f_nd
{
	int				*wait;
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
/*Sumilation*/
void	start_the_feast(t_nd inf, int id);
/*routine*/
void	*routine(void *arg);
/*printing the state of the philosopher*/
void	print_state(t_nd nd);
/*print function*/
void	*wht_the_philo_doing(void *arg);
/*stop the program and exit*/
void	out(t_nd nd);

#endif
