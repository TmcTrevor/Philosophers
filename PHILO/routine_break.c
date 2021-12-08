/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_break.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:43:36 by mokhames          #+#    #+#             */
/*   Updated: 2021/12/08 19:48:49 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo	*philo1;

	philo1 = (t_philo *)philo;
	if (philo1 == NULL || philo1->data->nb_meals == 0)
		return (NULL);
	while (1)
	{
		ft_eat(philo1);
		ft_sleep(philo1);
		ft_think(philo1);
	}
	return (philo1);
}

int	meals_eaten(t_philo *philo, int *k)
{
	int	i;

	i = philo->nb_meals;
	if (i == philo->data->nb_meals && philo->is_eating == 0)
	{
		*k = 0;
		return (0);
	}
	return (1);
}

void	break_point(t_philo *philo)
{
	int	i;
	int	k;

	k = 1;
	while (k)
	{
		i = 0;
		while (i < philo->data->nb_philo && !philo->is_eating)
		{
			pthread_mutex_lock(&philo->data->eating);
			if (!meals_eaten(&philo[i], &k))
				break ;
			if (!philo[i].is_eating && time_passed(philo[i].last_time_eaten)
				> (unsigned long)philo->data->t_death)
			{
				printstat(&philo[i], -1);
				k = 0;
				break ;
			}
			pthread_mutex_unlock(&philo->data->eating);
			i++;
		}
	}
}
