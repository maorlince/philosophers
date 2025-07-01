/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:07:16 by manon             #+#    #+#             */
/*   Updated: 2025/07/01 16:32:55 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_satiated(t_args *args)
{
	int	i;
	int	all_done;

	i = 0;
	all_done = 1;
	while (i < args->nbr_p)
	{
		pthread_mutex_lock(&args->philos[i].satiated_mutex);
		if (args->philos[i].nbr_loop != 0)
			all_done = 0;
		pthread_mutex_unlock(&args->philos[i].satiated_mutex);
		i++;
	}
	usleep(1000);
	return (all_done);
}

void	*ft_death(void *ptr)
{
	int		i;
	t_args	*args;

	args = (t_args *)ptr;
	while (1)
	{
		i = 0;
		while (i < args->nbr_p)
		{
			if (get_time() - args->philos[i].satiated > args->t_die)
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
		if (check_satiated(args))
			return (NULL);
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

static int	check_death(t_philo *philo)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(&args->dead_mutex);
	if (args->dead)
	{
		pthread_mutex_unlock(&args->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&args->dead_mutex);
	if (philo->nbr_loop == 0)
		return (1);
	return (0);
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
	while (!check_death(philo))
	{
		ft_eat(args, i);
		if (check_death(philo))
			break ;
		print_status(args, i, "sleep in their dreams🌕");
		usleep(args->t_sleep * 1000);
		print_status(args, i, "thinks like a genius⚡");
		usleep(1000);
	}
	return (NULL);
}
