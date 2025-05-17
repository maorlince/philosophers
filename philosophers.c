/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:33:32 by manon             #+#    #+#             */
/*   Updated: 2025/05/17 21:39:53 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

//philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;
	int	i;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (sign * res);
}

void live_likeem()
{
	pthread_mutex_lock (pthread_mutex_t * mutex);
	ft_printf("%d %s eat for the knowledges🍏\n", timestamp_in_m, philosopher[i]);
	pthread_mutex_unlock (pthread_mutex_t * mutex);
	pthread_mutex_lock (pthread_mutex_t * mutex);
	ft_printf("%d %s thinks like a genius⚡\n", timestamp_in_m, philosopher[i]);
	pthread_mutex_unlock (pthread_mutex_t * mutex);
	pthread_mutex_lock (pthread_mutex_t * mutex);
	ft_printf("%d %s sleep in yours dreams🌕\n", timestamp_in_m, philosopher[i]);
	pthread_mutex_unlock (pthread_mutex_t * mutex);
	pthread_mutex_lock (pthread_mutex_t * mutex);
	ft_printf("%d %s just died🗿\n", timestamp_in_m, philosopher[i]);
}

static void 	init_values(char *argv)
{
	unsigned long current;
	
	current = time();
	timestamp_in_m = (gettimeofday - current);
	
	number_of_philosopher = ft_atoi(argv[1]);
	time_to_die = argv[2];
	time_to_eat = argv[3];
	time_to_sleep = argv[4];
	number_of_times_each_philosopher_must_eat = 0;
	if (argv[5])
		number_of_times_each_philosopher_must_eat = argv[5];
	
}

int main(int argc, char **argv)
{
	int i;

	if (argc != 6)
		return (ft_printf("Erreur : nombre d'arguments incorrect"));
	init_values(argv);
	i = 0;
	while(i <= number_of_philosopher)
	{
		i++;
		pthread_create(&philosopher[i], NULL, live_likeem, NULL);
	}
}