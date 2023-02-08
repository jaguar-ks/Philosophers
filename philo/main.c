/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:53:01 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/08 03:25:42 by deman_wolf       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

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

int	check_inf(t_inf in, int ac)
{
	if (in.nb_ph <= 0 || in.t_d < 0 || in.t_e < 0 || in.t_s < 0)
		return (0);
	if (ac == 6 && (!in.h_m_e || *in.h_m_e <= 0))
		return (0);
	return (1);
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

	if (ac == 6 || ac == 5)
		nd.inf = init_info(ac, av);
	else
		return (error(-1));
	if (!check_inf(nd.inf, ac))
		return (error(-2));
	nd.phls = setting_up_table(nd.inf);
	nd.died = (int *)malloc(sizeof(int));
	if (!nd.died)
		return (1);
	*nd.died = nd.phls->st;
	printf("~|The address of nd.Died[%p]|\n", nd.died);
	start_the_feast(nd, nd.phls->philo_id);
	out(nd);
}
