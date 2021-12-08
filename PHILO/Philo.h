/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:14:39 by mokhames          #+#    #+#             */
/*   Updated: 2021/12/08 19:17:59 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int				achedmi;
	int				fed;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	eating;
}		t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			tid;
	long				nb_friends;
	int					nb_meals;
	int					is_eating;
	unsigned long long	begin;
	unsigned long long	last_time_eaten;
	t_data				*data;

}	t_philo;

int					ft_atoi(const char *str);
int					ft_strlen(char *str);
unsigned long long	time_passed(unsigned long long start);
unsigned long long	time_now(void);
void				sleepu(unsigned long long end);
void				*routine(void *philo);
void				ft_sleep(t_philo *philo);
void				ft_think(t_philo *philo);
void				ft_eat(t_philo *philo);
int					printstat(t_philo *philo, int mode);
int					meals_eaten(t_philo *philo, int e);
void				break_point(t_philo *philo);

#endif