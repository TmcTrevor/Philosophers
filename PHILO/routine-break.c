/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine-break.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:43:36 by mokhames          #+#    #+#             */
/*   Updated: 2021/12/08 18:45:12 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

// void	*routine(void *philo)
// {
// 	t_data	*data;
// 	int		i;

// 	data = (t_data *)philo;
// 	if (data == NULL || data->nb_meals == 0) 
// 	 	return (NULL);
// 	while (1)
// 	{
// 		ft_eat(data);
// 		ft_sleep(data);
// 		ft_think(data);
// 		i++;
// 	}
	
// 	return (data);
// //	printf("hello thread %d\n", philo1->id);
// }
void	*routine(void *philo)
{
	t_philo	*philo1;
	int		i;

	philo1 = (t_philo *)philo;
	if (philo1 == NULL || philo1->data->nb_meals == 0) 
	 	return (NULL);
	while (1)
	{
		ft_eat(philo1);
		ft_sleep(philo1);
		ft_think(philo1);
		i++;
	}
	
	return (philo1);
//	printf("hello thread %d\n", philo1->id);
}
int		meals_eaten(t_philo *philo, int e)
{
	int i;

	i = philo->nb_meals;
	if (i == philo->data->nb_meals && philo->is_eating == 0)
		return (0);
	return (1);
}

void	break_point(t_philo *philo)
{
	int i;
	int	k;

	k = 1;
	while (k)
	{
		i = 0;
		while (i < philo->data->nb_philo && !philo->is_eating)
		{
			pthread_mutex_lock(&philo->data->eating);
			if (!meals_eaten(&philo[i], i))
			{	
				k = 0;
				break;
			}
			if (!philo[i].is_eating  &&
				time_passed(philo[i].last_time_eaten) > (unsigned long)philo->data->t_death)
			{
				printstat(&philo[i], -1);
				k = 0;
				break;
			}
			pthread_mutex_unlock(&philo->data->eating);
			i++;
		}
	}
}