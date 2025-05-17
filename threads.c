/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:55:51 by manon             #+#    #+#             */
/*   Updated: 2025/05/13 16:04:16 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//creer pthread_t
//creer pthread_t_attr & attr ??
//cree fonction sleep & eat & thinks
//arg ??

int pthread_create(pthread_t *philo, const pthread_attr_t *attr, void *(*sleep)(void *), void *arg);
{
	//creer thread
}
//ex pthread_create(&thread, NULL, philosopher_routine, NULL);

int pthread_detach(pthread_t thread);
{
	//detache thread quand fini
}
//ex pthread_detach(thread);

int pthread_join(pthread_t thread, void **retval);
{
	//recupere valeur de retour d'un th
}
//ex pthread_join(thread, NULL);
