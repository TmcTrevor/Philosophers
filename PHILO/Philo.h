#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_data
{
	long			nb_philo;
	long			t_death;
	long			t_eat;
	long			t_sleep;
	int				nb_meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	eating;
}	   t_data;

typedef struct  s_philo
{
	int					id;
	pthread_t   		tid;
	int					nb_meals;
	int					is_eating;
	unsigned long long	begin;
	unsigned long long	last_time_eaten;

}	   t_philo;

int		ft_atoi(const char *str);
int		ft_strlen(char *str);

#endif