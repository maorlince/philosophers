/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:07:16 by manon             #+#    #+#             */
/*   Updated: 2025/06/30 16:54:06 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_death(void *ptr)
{
	int		i;
	t_args	*args;
	long	last_meal;

	args = (t_args *)ptr;
	while (1)
	{
		i = 0;
		while (i < args->nbr_p)
		{
			pthread_mutex_lock(&args->philos[i].satiated_mutex);
			last_meal = args->philos[i].satiated;
			pthread_mutex_unlock(&args->philos[i].satiated_mutex);
			if (get_time() - last_meal > args->t_die)
			{
				pthread_mutex_lock(&args->dead_mutex);
				args->dead = 1;
				pthread_mutex_unlock(&args->dead_mutex);
				pthread_mutex_lock(&args->print_mutex);
				printf("%ld Philo %d skip the game🗿\n",
					(get_time() - args->chrono), args->philos[i].id);
				pthread_mutex_unlock(&args->print_mutex);
				return (NULL);
			}
			i++;
		}
		int	all_done;
		int	j;
		all_done = 1;
		j = 0;
		while (j < args->nbr_p)
		{
			pthread_mutex_lock(&args->philos[j].satiated_mutex);
			if (args->philos[j].nbr_loop != 0)
				all_done = 0;
			pthread_mutex_unlock(&args->philos[j].satiated_mutex);
			j++;
		}
		if (all_done)
			return (NULL);
		usleep(1000);
	}
}

void	ft_eat(t_args *args, int i)
{
	if (i % 2 == 0)
	{
		pthread_mutex_lock (&args->forks[i]);
		print_status(args, i, "take a fork🍴");
		pthread_mutex_lock (&args->forks[(i + 1) % args->nbr_p]);
		print_status(args, i, "take an other fork🍽️");
	}
	else
	{
		pthread_mutex_lock (&args->forks[(i + 1) % args->nbr_p]);
		print_status(args, i, "take a fork🍴");
		pthread_mutex_lock (&args->forks[i]);
		print_status(args, i, "take an other fork🍽️");
	}
	print_status(args, i, "eat for the knowledges🍏");
	pthread_mutex_lock(&args->philos[i].satiated_mutex);
	args->philos[i].satiated = get_time();
	if (args->philos[i].nbr_loop > 0)
		args->philos[i].nbr_loop--;
	pthread_mutex_unlock(&args->philos[i].satiated_mutex);
	usleep(args->t_eat * 1000);
	pthread_mutex_unlock(&args->forks[i]);
	pthread_mutex_unlock(&args->forks[(i + 1) % args->nbr_p]);
}

void	*live_likeem(void *ptr)
{
	t_philo			*philo;
	t_args			*args;
	int				i;

	philo = (t_philo *)ptr;
	args = philo->args;
	i = (philo->id - 1);
	pthread_mutex_lock(&philo->satiated_mutex);
	philo->satiated = get_time();
	pthread_mutex_unlock(&philo->satiated_mutex);
	if (i % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&args->dead_mutex);
		if (args->dead)
		{
			pthread_mutex_unlock(&args->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&args->dead_mutex);
		if (philo->nbr_loop == 0)
			break ;
		ft_eat(args, i);
		pthread_mutex_lock(&args->dead_mutex);
		if (args->dead)
		{
			pthread_mutex_unlock(&args->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&args->dead_mutex);
		print_status(args, i, "sleep in their dreams🌕");
		usleep(args->t_sleep * 1000);
		print_status(args, i, "thinks like a genius⚡");
		usleep(1000);
	}
	return (NULL);
}
