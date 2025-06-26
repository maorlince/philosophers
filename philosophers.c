/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:33:32 by manon             #+#    #+#             */
/*   Updated: 2025/06/24 19:17:45 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//norme
//+de fun dans les printf +de MULTICOULEURS always for printf
//t_eat satiated when??
//securite init atoi -1 exit!
//nom exec philo?
//ordre changeant

//&& args->philos->nbr_loop != 0
//void	*ft_death(t_args *args, int i)
//{
//	if (get_time() - args->philos[i].satiated > args->t_die )
//	{
//		pthread_mutex_lock(&args->print_mutex);
//		printf("%ld Philo %d skip the game🗿\n",
//			(get_time() - args->chrono), i);
//		pthread_mutex_lock(&args->dead_mutex);
//		args->dead = 1;
//		pthread_mutex_unlock(&args->dead_mutex);
//		pthread_mutex_unlock(&args->print_mutex);
//		return (NULL);
//	}
//	return (NULL);
//}

void	*ft_death(void *ptr)
{
	int		i;
	t_args	*args;
	long last_meal;
	args = (t_args *)ptr;
	while (1)
	{
		i = 0;
		while (i < args->nbr_p)
		{
			pthread_mutex_lock(&args->philos[i].satiated_mutex);
			last_meal = args->philos[i].satiated;
			pthread_mutex_unlock(&args->philos[i].satiated_mutex);
			if (get_time() -last_meal > args->t_die )
			{
				pthread_mutex_lock(&args->print_mutex);
				printf("%ld Philo %d skip the game🗿\n",
					(get_time() - args->chrono), args->philos[i].id);
				pthread_mutex_lock(&args->dead_mutex);
				args->dead = 1;
				pthread_mutex_unlock(&args->dead_mutex);
				pthread_mutex_unlock(&args->print_mutex);
				return (NULL);
			}
			i++;
		}
		usleep(100);
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
	usleep(args->t_eat * 1000);
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
	while (philo->nbr_loop != 0)
	{
		pthread_mutex_lock(&args->dead_mutex);
		if (args->dead)
		{
			pthread_mutex_unlock(&args->dead_mutex);
			break;
		}
		pthread_mutex_unlock(&args->dead_mutex);
		ft_eat(args, i);
		pthread_mutex_lock(&args->dead_mutex);
		if (args->dead)
		{
			pthread_mutex_unlock(&args->dead_mutex);
			pthread_mutex_unlock(&args->forks[i]);
			pthread_mutex_unlock(&args->forks[(i + 1) % args->nbr_p]);
			break;
		}
		pthread_mutex_unlock(&args->dead_mutex);
		pthread_mutex_lock(&philo->satiated_mutex);
		philo->satiated = get_time();
		philo->nbr_loop--;
		pthread_mutex_unlock(&philo->satiated_mutex);
		// usleep(args->t_eat);
		pthread_mutex_unlock (&args->forks[i]);
		pthread_mutex_unlock (&args->forks[(i + 1) % args->nbr_p]);
		print_status(args, philo->id, "sleep in their dreams🌕");
		usleep(args->t_sleep * 1000);
		print_status(args, philo->id, "thinks like a genius⚡");
		usleep(500);
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
		if (pthread_mutex_init(&philos[i].satiated_mutex, NULL) != 0)
			return (1);
		philos[i].id = i + 1;
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
	int			i;
	t_args		args;
	t_philo		*philos;
	pthread_t	verif_death;

	i = 0;
	if (argc != 5 && argc != 6)
		return (printf("[Erreur : nombre d'args incorrect]\n"));
	if (init_values(argv, &args))
		return (printf("[Erreur : init_values]\n"));
	philos = malloc(sizeof(t_philo) * args.nbr_p);
	if (!philos)
		return (printf("[Erreur : malloc philos]\n"));
	args.philos = philos;
	if (init_struct(philos, &args))
		return (printf("[Erreur : init_struct]\n"));
	pthread_create(&verif_death, NULL, ft_death, &args);
	while (i < args.nbr_p)
		pthread_join(args.t_p[i++], NULL);
	pthread_join(verif_death, NULL);
	while (i--)
	{
		pthread_mutex_destroy(&args.forks[i]);
		pthread_mutex_destroy(&philos[i].satiated_mutex);
	}
	clean_all(philos, &args);
}
