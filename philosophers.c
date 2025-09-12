/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:33:32 by manon             #+#    #+#             */
/*   Updated: 2025/09/12 09:26:26 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_values(char **argv, t_args *args)
{
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
	if (!args->t_p || !args->forks || args->nbr_p <= 0 || args->t_die < 0
		|| args->t_eat < 0 || args->t_sleep < 0)
		return (1);
	if (pthread_mutex_init(&args->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&args->dead_mutex, NULL) != 0)
		return (1);
	return (0);
}

static int	init_struct(t_philo *philos, t_args *args)
{
	int	i;

	i = 0;
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
		i++;
	}
	i = 0;
	while (i < args->nbr_p)
	{
		if (pthread_create(&args->t_p[i], NULL, live_likeem, &philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	verif(t_philo *philos, t_args *args)
{
	if (!philos)
		return (printf("[Erreur : malloc philos]\n"));
	args->philos = philos;
	if (init_struct(philos, args))
		return (printf("[Erreur : init_struct]\n"));
	if (args->nbr_p == 1)
	{
		usleep(args->t_die * 1000);
		print_status(args, 0, "skip the game🗿");
		clean_all(philos, args);
		return (1);
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
		return (printf("[Erreur : values incorrectes]\n"));
	philos = malloc(sizeof(t_philo) * args.nbr_p);
	if (verif(philos, &args))
		return (0);
	if (pthread_create(&verif_death, NULL, ft_death, &args) != 0)
		return (printf("[Erreur : pthread_create death]\n"));
	while (i < args.nbr_p)
		pthread_join(args.t_p[i++], NULL);
	pthread_join(verif_death, NULL);
	clean_all(philos, &args);
}
