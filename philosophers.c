/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:33:32 by manon             #+#    #+#             */
/*   Updated: 2025/05/28 17:29:59 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

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
unsigned long	get_time(void)
{
	struct timeval	tv;
	//unsigned long	last_update;
	//unsigned long	current;

	gettimeofday (&tv, NULL);
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	//current = get_time();
	////|| current = (tv.tv_sec * 1000) + (tv.tv_usec / 1000)
	//if (current - last_update >= 500) //500 = demi seconde
	//{
	//	//[...]
	//	last_update = current;
	//}
}

void live_likeem(t_args *args, int i)
{
	pthread_mutex_lock (&args->t_f[i]);
	ft_printf("%d %s eat for the knowledges🍏\n", args->chrono, i);
	usleep(100);
	pthread_mutex_unlock (&args->t_f[i]);
	ft_printf("%d %s thinks like a genius⚡\n", args->chrono, i);
	usleep(100);
	ft_printf("%d %s sleep in yours dreams🌕\n", args->chrono, i);
	usleep(100);
}

static void 	init_values(char **argv, t_args *args)
{
	unsigned long current;

	current = get_time();
	args->chrono = (gettimeofday - current);
	
	args->nbr_p = ft_atoi(argv[1]);
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	args->nbr_loop = 0;
	if (argv[5])
		args->nbr_loop =  ft_atoi(argv[5]);
	else
		args->nbr_loop = -1;
	
}

int main(int argc, char **argv)
{
	int i;
	t_args 	args;
	pthread_t t_p;

	if (argc != 6)
		return (ft_printf("Erreur : nombre d'arguments incorrect"));
	i = 0;
	init_values(argv, &args);
	pthread_mutex_init(&args.t_f[i], NULL);
	while(i <= args.nbr_p)
	{
		i++;
		pthread_create(&args.t_p[i], NULL, live_likeem, (void *)&args);
	}
    pthread_join(args.t_p[i], NULL);
    pthread_mutex_destroy(&args.t_f[i]);
}