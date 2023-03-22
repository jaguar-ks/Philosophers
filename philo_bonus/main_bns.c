/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:48:16 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/22 22:48:16 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bns.h"

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

int	error(int er)
{
	if (er == -1)
		write(2, "Error: Invalid number of arguments\n", 36);
	if (er == -2)
		write(2, "Error: Wrong value of some arguments\n", 38);
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
	return (in);
}

int	check_inf(t_inf in, int ac)
{
	if (in.nb_ph <= 0 || in.t_d < 0 || in.t_e < 0 || in.t_s < 0)
		return (0);
	if (ac == 6 && (!in.h_m_e || *in.h_m_e <= 0))
		return (0);
	return (1);
}

int main(int ac, char **av)
{
    t_nd    nd;

    if (ac == 6 || ac ==5)
        nd.inf = init_info(ac, av);
    else
		return (error(-1));
    if (!check_inf(nd.inf, ac))
		return (error(-2));
    nd.ph = setting_up_table(nd.inf);
    start_the_feast(nd);
}
