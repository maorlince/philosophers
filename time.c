/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:35:15 by manon             #+#    #+#             */
/*   Updated: 2025/05/17 19:30:42 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	time(void)
{
	struct timeval	tv;
	unsigned long	last_update;
	unsigned long	current;

	gettimeofday (&tv, NULL);
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	current = time();
	//|| current = (tv.tv_sec * 1000) + (tv.tv_usec / 1000)

	if (current - last_update >= 500) //500 = demi seconde
	{
		//[...]
		last_update = current;
	}
}