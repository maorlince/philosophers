/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:35:15 by manon             #+#    #+#             */
/*   Updated: 2025/05/13 15:53:19 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	tv;
	unsigned long	last_update;
	unsigned long	current;

	gettimeofday (&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	current = get_time();
	//|| current = (tv.tv_sec * 1000) + (tv.tv_usec / 1000)

	if (current - last_update >= 500) //500 = demi seconde
	{
		//[...]
		last_update = current;
	}
}