/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:38:13 by manon             #+#    #+#             */
/*   Updated: 2025/06/13 18:42:57 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "ft_printf/ft_printf.h"

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

//editeur de lien -lpthread et compilateur -D_REENTRANT et/ou -DLinux
// valgrind --tool=helgrind ./philo 5 610 200 200 3

typedef struct s_args
{
	int				nbr_p;
	int				loop;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	unsigned long	chrono;
	//int				died;
	//pthread_mutex_t	dead_mutex;
	pthread_t		*t_p;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
}	t_args;

typedef struct s_philo
{
	unsigned long	satiated;
	int				id;
	int				nbr_loop;
	t_args			*args;
}	t_philo;

//utils.c
int				ft_atoi(const char *str);
unsigned long	get_time(void);
void			print_status(t_args *args, int i, const char *str);

#endif
