#include "Philo.h"


t_philo *init_philos(t_data *data)
{
	int	i;
	t_philo *philos;

	i = 0;
	//printf("%d\n", data->nb_philo);
	philos = NULL;
	philos = (t_philo *)malloc((data->nb_philo) * sizeof(t_philo));
	while (i < data->nb_philo)
	{
		//philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].nb_meals = 0;
		philos[i].is_eating = 0;
		philos[i].nb_friends = data->nb_philo;
		philos[i].last_time_eaten = time_now();
		philos[i].begin = philos[0].last_time_eaten;
		i++;
	}
	return (philos);
}
t_philo *init(t_data *data)
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

int	printstat(t_data *data, int mode)
{
	if (pthread_mutex_lock(&data->write))
		return (1);
	if (mode == -1)
		printf("philo %d died\n", data->achedmi);
	if (mode == 0)
		printf("philo %d is thinking\n", data->achedmi);
	if (mode == 1)
		printf("philo %d is eating\n",data->achedmi);
	if (mode == 2)
		printf("philo %d is sleeping\n",data->achedmi);
	if (pthread_mutex_unlock(&data->write))
		return (1);
	return (0);
}

void	ft_eat(t_data *data)
{
	int	lfork;
	int	rfork;
	int	i;

	i = data->achedmi;
	if (data->achedmi % 2 == 0)
	{
		rfork =	(i + 1) % data->nb_philo;
		lfork = i;
	}
	else
	{
		lfork = (i + 1) % data->nb_philo;
		rfork = i;
	}
	pthread_mutex_lock(&data->forks[lfork]);
	pthread_mutex_lock(&data->forks[rfork]);
	pthread_mutex_lock(&data->eating);
	data->philos[i].last_time_eaten = time_now();
	pthread_mutex_unlock(&data->eating);
	data->philos[i].is_eating = 1;
	printstat(data, 1);
	usleep((data->t_eat * 1000) - 1000);
	sleepu(data->philos[i].last_time_eaten + data->t_eat);
	pthread_mutex_lock(&data->eating);
	data->philos[i].is_eating = 0;
	data->philos[i].nb_meals++;
	if (data->philos[i].nb_meals == data->nb_philo)
		data->fed++;
	pthread_mutex_unlock(&data->eating);
	pthread_mutex_unlock(&data->forks[lfork]);
	pthread_mutex_unlock(&data->forks[rfork]);
}

void	ft_think(t_data *data)
{
	printstat(data, 0);
}

void	ft_sleep(t_data *data)
{
	unsigned long long	before_sleep;

	before_sleep = time_now();
	//printf("dasdasd\n");
	printstat(data, 2);
	usleep((data->t_sleep * 1000) - 10000);
	sleepu(data->t_sleep + before_sleep);
}

void	*routine(void *philo)
{
	t_data *data;

	data = (t_data *)philo;
	if (data == NULL || data->nb_meals == 0) 
	 	return (NULL);
	int i = 0;
	while (1)
	{
		ft_eat(data);
		ft_sleep(data);
		ft_think(data);
		i++;
	}
	return philo;
//	printf("hello thread %d\n", philo1->id);
}

int		meals_eaten(t_data *data, int e)
{
	int i;

	i = data->philos[e].nb_meals;
	if (i == data->nb_meals && data->philos[e].is_eating == 0)
		return (0);
	return (1);
}

void	break_point(t_data *data)
{
	int i;
	int	k;

	k = 1;
	while (k)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->eating);
			if (!meals_eaten(data, i))
			{	
				k = 0;
				break;
			}
			if (data->philos[i].is_eating  &&
				time_passed(data->philos[i].last_time_eaten) > data->t_death)
			{
				printstat(data, -1);
				break;
				k = 0;
			}
			pthread_mutex_unlock(&data->eating);
			i++;
		}
	}
}

void dining(t_data *data)
{
	int 	i;
	//t_philo	*philos;

	i = 0;
	data->philos = init(data);
	while (i < data->nb_philo)
	{
		data->achedmi = i + 1;
		if (pthread_create(&data->philos[i].tid, NULL, routine, data))
			printf("error creating thread\n");
		usleep(1);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].tid, NULL);
		i++;
	}
	break_point(data);

}

int parse_data(int ac, char **av, t_data *data)
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
	data->philos = NULL;
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	return (1);
}

int main(int ac, char **av)
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
	//printf("adsads\n");
	return (0);
}