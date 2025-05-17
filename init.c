/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:22:53 by manon             #+#    #+#             */
/*   Updated: 2025/05/16 18:28:15 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void init_philos(char *arv)
{
	int n;
	int i;

	n = ft_atoi(arv);
	i = 0;
	while(i <= n)
	{
		i++;
		pthread_create(&philosopher, NULL, philosopher_routine, NULL);
	}
}