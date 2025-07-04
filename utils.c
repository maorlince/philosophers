/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:02:16 by manon             #+#    #+#             */
/*   Updated: 2025/07/01 19:49:36 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	long	res;
	int		i;

	i = 0;
	res = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if (res > 2147483647)
			return (-1);
	}
	if (str[i] != '\0' || i == 0)
		return (-1);
	return ((int)res);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday (&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_args *args, int i, const char *str)
{
	int	current;

	pthread_mutex_lock(&args->dead_mutex);
	if (args->dead)
	{
		pthread_mutex_unlock(&args->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&args->dead_mutex);
	pthread_mutex_lock(&args->print_mutex);
	current = (get_time() - args->chrono);
	printf("%d Philo %d %s\n", current, i + 1, str);
	pthread_mutex_unlock(&args->print_mutex);
}

void	clean_all(t_philo *philos, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_p)
	{
		pthread_mutex_destroy(&args->forks[i]);
		pthread_mutex_destroy(&philos[i].satiated_mutex);
		i++;
	}
	pthread_mutex_destroy(&args->print_mutex);
	pthread_mutex_destroy(&args->dead_mutex);
	free(args->t_p);
	free(args->forks);
	free(philos);
}

int	is_still_alive(int i, t_args *args)
{
	unsigned long	res;

	pthread_mutex_lock(&args->philos[i].satiated_mutex);
	res = get_time() - args->philos[i].satiated;
	pthread_mutex_unlock(&args->philos[i].satiated_mutex);
	if (res > (long unsigned int)args->t_die)
		return (1);
	return (0);
}
