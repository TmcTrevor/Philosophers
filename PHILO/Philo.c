/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:18:32 by mokhames          #+#    #+#             */
/*   Updated: 2021/12/08 19:23:01 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

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

// void	ft_eat(t_philo *philo)
// {
// 	int lfork;
// 	int rfork;

// 	if (philo->id % 2 == 0)
// 	{
// 		rfork = philo->id  % philo->nb_friends;
// 		lfork = philo->id;
// 	}
// 	else
// 	{
// 		lfork = philo->id % philo->nb_friends;
// 		rfork = philo->id;
// 	}
	
	
// 	printf("philo %d is eating\n", philo->id);
// }

// void	*routine(void *philo)
// {
// 	t_philo *philo1;

// 	philo1 = (t_philo *)philo;
// 	 if (philo1 == NULL) 
// 	 	return (NULL);
// 	while (1)
// 	{
// 		//printf("sadasd\n");
// 		ft_eat(philo1);
// 		// ft_sleep(philo1);
// 		// ft_think(philo1);
// 	}
// 	return philo;
// //	printf("hello thread %d\n", philo1->id);
// }

int	printstat(t_philo *philo, int mode)
{
	t_data *data;

	data = philo->data;
	if (pthread_mutex_lock(&philo->data->write))
		return (1);
	if (mode == -1)
	{
		printf("%llu philo %d died\n", time_passed(philo->begin), philo->id);
		return (0);
	}
	if (mode == 0)
		printf("%llu philo %d is thinking\n", time_passed(philo->begin), philo->id);
	if (mode == 1)
		printf("%llu philo %d is eating\n", time_passed(philo->begin), philo->id);
	if (mode == 2)
		printf("%llu philo %d is sleeping\n", time_passed(philo->begin), philo->id);
	if (mode == 3)
		printf("%llu philo %d has taken a fork\n", time_passed(philo->begin), philo->id);
	if (pthread_mutex_unlock(&philo->data->write))
		return (1);
	return (0);
}

// void	ft_eat(t_data *data)
// {
// 	int	lfork;
// 	int	rfork;
// 	int	i;

// 	i = data->achedmi;
// 	if (data->achedmi % 2 == 0)
// 	{
// 		rfork =	(i + 1) % data->nb_philo;
// 		lfork = i;
// 	}
// 	else
// 	{
// 		lfork = (i + 1) % data->nb_philo;
// 		rfork = i;
// 	}
// 	pthread_mutex_lock(&data->forks[lfork]);
// 	pthread_mutex_lock(&data->forks[rfork]);
// 	pthread_mutex_lock(&data->eating);
// 	data->philos[i].last_time_eaten = time_now();
// 	pthread_mutex_unlock(&data->eating);
// 	data->philos[i].is_eating = 1;
// 	printstat(data, 1);
// 	usleep((data->t_eat * 1000) - 1000);
// 	sleepu(data->philos[i].last_time_eaten + data->t_eat);
// 	pthread_mutex_lock(&data->eating);
// 	data->philos[i].is_eating = 0;
// 	data->philos[i].nb_meals++;
// 	if (data->philos[i].nb_meals == data->nb_philo)
// 		data->fed++;
// 	pthread_mutex_unlock(&data->eating);
// 	pthread_mutex_unlock(&data->forks[lfork]);
// 	pthread_mutex_unlock(&data->forks[rfork]);
// }

// void	ft_think(t_data *data)
// {
// 	printstat(data, 0);
// }

// void	ft_sleep(t_data *data)
// {
// 	unsigned long long	before_sleep;

// 	before_sleep = time_now();
// 	//printf("dasdasd\n");
// 	printstat(data, 2);
// 	usleep((data->t_sleep * 1000) - 10000);
// 	sleepu(data->t_sleep + before_sleep);
// }




void	dining(t_data *data)
{
	int 	i;
	t_philo	*philo;

	i = 0;
	philo = init(data);
	while (i < data->nb_philo)
	{
		data->achedmi = i + 1;
		if (pthread_create(&philo->tid, NULL, routine, &philo[i]))
			printf("error creating thread\n");
		usleep(100);
		i++;
	}
	break_point(philo);

}

int	parse_data(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	if (data->nb_philo == 0 || data->nb_philo > 200)
	{
		printf("wrong number of philos\n");
		return (0);
	}
	data->t_death = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->nb_meals = -1;
	data->fed = 0;
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac == 5 || ac == 6)
	{
		data = (t_data *)malloc(sizeof(t_data));
		if (!parse_data(ac, av, data))
		{
			free(data);
			exit(0);
		}
		dining(data);
	}
	else
		printf("wrong number of argument\n");
	return (0);
}