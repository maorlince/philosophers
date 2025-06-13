/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:02:16 by manon             #+#    #+#             */
/*   Updated: 2025/06/11 18:46:17 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' && i > 1)
		return (-1);
	return (res);
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

	pthread_mutex_lock(&args->print_mutex);
	current = (get_time() - args->chrono);
	ft_printf("%d Philo %d %s\n", current, i, str);
	pthread_mutex_unlock(&args->print_mutex);
}
