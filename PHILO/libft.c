#include "Philo.h"

int		ft_atoi(const char *str)
{
	int i;
	int atoi;
	int sign;

	i = 0;
	atoi = 0;
	sign = 1;
	while (str[i] && ((str[i] >= 8 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] > 47 && str[i] < 58)
		atoi = atoi * 10 + str[i++] - '0';
	return (atoi * sign);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}