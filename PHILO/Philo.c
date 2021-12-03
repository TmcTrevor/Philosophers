#include "Philo.h"


void init_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	philos = (t_philo *)malloc((data->nb_philo) * sizeof(t_philo));
	while (i < data->nb_philo)
	{
		philos[i].id = i;
		philos[i].nb_meals = 0;
		philos[i].is_eating = 0;
		philos[i].last_time_eaten = time_now();
		philos[i].begin = philos[0].last_time_eaten;
		i++;
	}
}
void init(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	data->forks = malloc((data->nb_philo) * sizeof(pthread_mutex_t));
	while (i++ < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->eating, NULL);
	init_philos(philos, data);
}

void dining(t_data *data)
{
	int 	i;
	t_philo	*philos;

	init(data, philos);
	while (i < data->nb_philo)
	{
		if (pthread_create(&philos[i].tid, NULL, routine, philos + i))
			printf("error creating thread\n");
		i++;
	}

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
	data->t_death = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->nb_meals = -1;
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
	return (0);
}