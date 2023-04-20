/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:50:01 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/20 13:29:08 by faksouss         ###   ########.fr       */
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
	int				nb_ph; // Number of philosophers setting around the table
	int				t_d; // Time to die if they didn't eat
	int				t_e; // Time each philosopher should spent eating
	int				t_s; // Time each philosopher should spent sleeping
	int				*h_m_e; // The optional argiment of how many time should each philosopher eat
	int				lp; // This variable its indicate how many time the simulation had looped
	pthread_mutex_t	prnt; // This mutex is used to protect the the thread writing the state of the philosopher
	pthread_t		wrtr; // This is the thread used to write the state of the philosopher
	pthread_mutex_t	wt; // This mutex is used to wait for the philosopher who is writing what he is doing
}	t_inf;

typedef struct f_philo
{
	pthread_t			thrd_id; // The thread ID
	int					philo_id; // The philosopher ID or his place around the table
	unsigned long long	ct; // The philosopher current time
	int					t_l; // The time left for the philosopher to live
	int					st; // The state of the philosopher or what is he doing on the current time
	pthread_mutex_t		f; // The mutex that represent the fork
	struct f_philo		*nxt; // The pointer to the next philosopher
}	t_philo;

typedef struct f_nd
{
	int				*wait; // The intiger pointer that used to send to pthread_join() function to store the rotine return value
	struct f_inf	inf; // The data intred by the user
	struct f_philo	*phls; // The linked list of the philosophers
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
