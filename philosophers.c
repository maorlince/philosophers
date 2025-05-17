/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:33:32 by manon             #+#    #+#             */
/*   Updated: 2025/05/16 19:26:48 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

//philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

int	ft_atoi(const char *str)
{
	int	signe;
	int	res;
	int	i;

	i = 0;
	res = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (signe * res);
}

void live_likeem()
{
	ft_printf("eat\n");
	pthread_mutex_lock (pthread_mutex_t * mutex);
	ft_printf("thinks\n");
	pthread_mutex_unlock (pthread_mutex_t * mutex);
	ft_printf("sleep\n");
}

static void 	init_values(char *argv)
{
	philos = ft_atoi(argv[1]);
	t_die = argv[2];
	t_eat = argv[3];
	t_sleep = argv[4];
	[t_eat_all]
}

int main(int argc, char **argv)
{
	int n;
	int i;

	if (argc != 6)
		return (ft_printf("Erreur : nombre d'arguments incorrect"));
	init_values(argv);
	n = ft_atoi(argv[1]);
	i = 0;
	while(i <= n)
	{
		i++;
		pthread_create(&philosopher[i], NULL, live_likeem, NULL);
	}
}