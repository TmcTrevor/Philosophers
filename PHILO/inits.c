/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:26:35 by mokhames          #+#    #+#             */
/*   Updated: 2021/12/08 19:49:06 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *)malloc((data->nb_philo) * sizeof(t_philo));
	while (i < data->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].nb_meals = 0;
		philos[i].is_eating = 0;
		philos[i].nb_friends = data->nb_philo;
		philos[i].last_time_eaten = time_now();
		philos[i].begin = philos[0].last_time_eaten;
		philos[i].data = data;
		i++;
	}
	return (philos);
}

t_philo	*init(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = 0;
	data->forks = malloc((data->nb_philo) * sizeof(pthread_mutex_t));
	while (i++ < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->eating, NULL);
	philos = init_philos(data);
	return (philos);
}
