/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:48:49 by mokhames          #+#    #+#             */
/*   Updated: 2021/12/08 18:53:53 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

void	ft_eat(t_philo *philo)
{
	int	lfork;
	int	rfork;
	int	i;

	i = philo->id;
	if (i % 2 == 0)
	{
		rfork =	(i + 1) % philo->data->nb_philo;
		lfork = i;
	}
	else
	{
		lfork = (i + 1) % philo->data->nb_philo;
		rfork = i;
	}
	pthread_mutex_lock(&philo->data->forks[lfork]);
	printstat(philo, 3);
	pthread_mutex_lock(&philo->data->forks[rfork]);
	printstat(philo, 3);
	pthread_mutex_lock(&philo->data->eating);
	philo->last_time_eaten = time_now();
	pthread_mutex_unlock(&philo->data->eating);
	philo->is_eating = 1;
	printstat(philo, 1);
	usleep((philo->data->t_eat * 1000) - 1000);
	sleepu(philo->last_time_eaten + philo->data->t_eat);
	pthread_mutex_lock(&philo->data->eating);
	philo->is_eating = 0;
	philo->nb_meals++;
	if (philo->nb_meals == philo->data->nb_philo)
		philo->data->fed++;
	pthread_mutex_unlock(&philo->data->eating);
	pthread_mutex_unlock(&philo->data->forks[lfork]);
	pthread_mutex_unlock(&philo->data->forks[rfork]);
}

void	ft_think(t_philo *philo)
{
	printstat(philo, 0);
}

void	ft_sleep(t_philo *philo)
{
	unsigned long long	before_sleep;

	before_sleep = time_now();
	//printf("dasdasd\n");
	printstat(philo, 2);
	usleep((philo->data->t_sleep * 1000) - 10000);
	sleepu(philo->data->t_sleep + before_sleep);
}
