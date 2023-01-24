/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:53:19 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/24 18:10:31 by faksouss         ###   ########.fr       */
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
		write(2, "Error: Detaching thread faild\n", 31);
	if (er == -4)
		write(2, "Error: Destroying mutex faild\n", 31);
	return (1);
}
