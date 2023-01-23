/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:50:01 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/23 16:04:28 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdlib.h>
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

/*initialasing the informations needed*/
t_inf	init_info(int ac, char **av);
/*errors handlling*/
int		error(int er);

#endif
