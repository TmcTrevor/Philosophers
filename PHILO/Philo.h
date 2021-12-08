#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct  s_philo
{
	int					id;
	pthread_t   		tid;
	long				nb_friends;
	int					nb_meals;
	int					is_eating;
	unsigned long long	begin;
	unsigned long long	last_time_eaten;
//	t_data				*data;

}	   t_philo;

typedef struct s_data
{
	long			nb_philo;
	long			t_death;
	long			t_eat;
	long			t_sleep;
	int				nb_meals;
	int				achedmi;
	int				fed;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	eating;
	t_philo			*philos;
}	   t_data;



int		ft_atoi(const char *str);
int		ft_strlen(char *str);
unsigned long long	time_passed(unsigned long long	start);
unsigned long long	time_now(void);
void	sleepu(unsigned long long end);
#endif