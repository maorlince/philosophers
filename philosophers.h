/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:38:13 by manon             #+#    #+#             */
/*   Updated: 2025/05/28 16:22:05 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "ft_printf/ft_printf.h"

# include <sys/time.h>
# include <pthread.h>

//editeur de lien -lpthread et compilateur -D_REENTRANT et/ou -DLinux
// valgrind --tool=helgrind ./philo 5 610 200 200 3

	typedef struct s_p
	{
		pthread_t	philosopher;
		int 		i;
	
	}	t_p;

	typedef	struct s_f
	{
		pthread_mutex_t	fork_mutex;
		int				i;
	}	t_f;

	typedef struct s_args
	{
		int				nbr_p;
		int				t_die;
		int				t_eat;
		int				t_sleep;
		int				nbr_loop;
		long			chrono;
		pthread_t		*t_p;
		pthread_mutex_t	*t_f;
	}	t_args;

#endif
