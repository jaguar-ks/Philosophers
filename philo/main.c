/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:53:01 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/12 23:55:38 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	error(int er)
{
	if (er == -1)
		write(2, "Error: Invalid number of arguments\n", 36);
	if (er == -2)
		write(2, "Error: Wrong value of some arguments\n", 38);
	if (er == -3)
		write(2, "Error: Dinamical allocation faild\n", 35);
	return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		s;
	long	r;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		s *= -1;
	if (s < 0 || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - 48);
		i++;
	}
	return (r * s);
}

t_inf	init_info(int ac, char **av)
{
	t_inf	in;

	in.nb_ph = ft_atoi(av[1]);
	in.t_d = ft_atoi(av[2]);
	in.t_e = ft_atoi(av[3]);
	in.t_s = ft_atoi(av[4]);
	if (ac == 6)
	{
		in.h_m_e = (int *)malloc(sizeof(int));
		if (!in.h_m_e)
			return (in);
		*in.h_m_e = ft_atoi(av[5]);
	}
	else
		in.h_m_e = NULL;
	in.lp = 0;
	pthread_mutex_init(&in.prnt, NULL);
	pthread_mutex_init(&in.wt, NULL);
	return (in);
}

int	main(int ac, char **av)
{
	t_nd	nd;
	t_philo	*tmp;

	init_nd(ac, av, &nd);
	if (nd.i != 0)
		return (error(nd.i));
	tmp = nd.phls;
	printf("philo ID >> %d\n", tmp->philo_id);
	while (1)
	{
		pthread_create(&nd.phls->thrd_id, NULL, &routine, &nd);
		usleep(80);
		pthread_mutex_lock(&nd.d);
		if (*nd.died == 'd')
			break ;
		pthread_mutex_unlock(&nd.d);
		nd.phls = nd.phls->nxt;
		nd.inf.lp += (nd.phls->philo_id == nd.inf.nb_ph);
		if ((nd.inf.h_m_e && *nd.inf.h_m_e == nd.inf.lp + 1))
			break ;
	}
	nd.phls = tmp;
	out(nd);
}
	// start_the_feast(nd, nd.phls->philo_id);
