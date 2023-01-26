/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_inf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:42:50 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/25 15:47:15 by deman_wolf       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

long	ft_atoi(const char *str)
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

int	check_inf(t_inf in)
{
	if (in.nb_ph <= 0 || in.t_d < 0 || in.t_e < 0 || in.t_s < 0)
		return (0);
	if (in.h_m_e && *in.h_m_e < 0)
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
	in.h_m_e = (long *)malloc(sizeof(long));
	if (ac == 6)
		*in.h_m_e = ft_atoi(av[5]);
	else
	{
		free(in.h_m_e);
		in.h_m_e = NULL;
	}
	if (!check_inf(in))
		exit(error(-2));
	in.ct = 0;
	return (in);
}
