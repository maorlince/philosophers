/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:33:32 by manon             #+#    #+#             */
/*   Updated: 2025/06/17 14:22:06 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//norme
//+de fun dans les printf +de MULTICOULEURS always for printf
//t_die? INTUABLES LES MECS
//t_eat satiated when??
//securite init atoi -1 exit!
//nom exec philo?
//time bug et print si flag

void	*ft_death(void *ptr)
{
	t_args	*args = (t_args *)ptr;
	int	current;
	int i;
	
	while (1)
	{
		i = 0;
		while (i < args->nbr_p)
		{
			if (get_time() - args->philos[i].satiated > args->t_die)
			{
				pthread_mutex_lock(&args->print_mutex);
				current = (get_time() - args->chrono);
				printf("%d Philo %d skip the game🗿\n", current, i);
				pthread_mutex_lock(&args->dead_mutex);
				args->dead = 1;
				pthread_mutex_unlock(&args->dead_mutex);
				pthread_mutex_unlock(&args->print_mutex);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
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
}

void	*live_likeem(void *ptr)
{
	t_philo			*philo;
	t_args			*args;
	int				i;

	philo = (t_philo *)ptr;
	args = philo->args;
	i = philo->id;
	philo->satiated = get_time();
	if (i % 2 == 0)
		usleep(100);
	while (philo->nbr_loop > 0 && args->dead != 1)
	{
		ft_eat(args, i);
		philo->satiated = get_time();
		usleep(args->t_eat);
		pthread_mutex_unlock (&args->forks[i]);
		pthread_mutex_unlock (&args->forks[(i + 1) % args->nbr_p]);
		print_status(args, philo->id, "sleep in their dreams🌕");
		usleep(args->t_sleep);
		print_status(args, philo->id, "thinks like a genius⚡");
		philo->nbr_loop--;
	}
	return (NULL);
}

static int	init_values(char **argv, t_args *args)
{
		//int i;
	//i = 0;
	//while (argv[i])
	//{
	//	if (ft_atoi(argv[i]) == -1)
	//		exit (0);
	//	i++;
	//}
	args->chrono = get_time();
	args->nbr_p = ft_atoi(argv[1]);
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	args->t_p = malloc(sizeof(pthread_t) * args->nbr_p);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->nbr_p);
	args->dead = 0;
	if (argv[5])
		args->loop = ft_atoi(argv[5]);
	else
		args->loop = -1;
	if (!args->t_p || !args->forks || args->nbr_p <= 0 || args->t_die <= 0
			|| args->t_eat <= 0 || args->t_sleep <= 0)
		return (1);
	return (0);
}

static int	init_struct(t_philo *philos, t_args *args)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&args->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&args->dead_mutex, NULL) != 0)
		return (1);
	while (i < args->nbr_p)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
			return (1);
		philos[i].id = i;
		philos[i].args = args;
		philos[i].satiated = get_time();
		philos[i].nbr_loop = args->loop;
		if (pthread_create(&args->t_p[i], NULL, live_likeem, &philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	t_args	args;
	t_philo	*philos;

	i = 0;
	if (argc != 5 && argc != 6)
		return (printf("[Erreur : nombre d'args incorrect]\n"));
	if (init_values(argv, &args))
		return (printf("[Erreur : init_values]\n"));
	philos = malloc(sizeof(t_philo) * args.nbr_p);
	if (!philos)
		return (printf("[Erreur : malloc philos]\n"));
	if (init_struct(philos, &args))
		return (printf("[Erreur : init_struct]\n"));
	args.philos = philos; 
	pthread_t verif_death;
	pthread_create(&verif_death, NULL, ft_death, &args);
	while (i < args.nbr_p)
		pthread_join(args.t_p[i++], NULL);
	pthread_join(verif_death, NULL);
	while (i != 0)
	{
		i--;
		pthread_mutex_destroy(&args.forks[i]);
	}
	pthread_mutex_destroy(&args.print_mutex);
	pthread_mutex_destroy(&args.dead_mutex);
	free(args.t_p);
	free(args.forks);
	free(philos);
}
