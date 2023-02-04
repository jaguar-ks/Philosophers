/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:53:19 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/05 00:01:47 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	error(int er)
{
	if (er == -1)
		write(2, "Error: Invalid number of arguments\n", 36);
	if (er == -2)
		write(2, "Error: Wrong value of some arguments\n", 38);
	return (1);
}
