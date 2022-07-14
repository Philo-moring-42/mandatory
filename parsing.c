#include "philo.h"

int	parsing(int argc, char **argv, t_rule *rule)
{
	if (argc != 5 && argc != 6)
		return (FAIL);
	rule->num_of_philo = ft_atoi(argv[1]);
	rule->time_to_die = ft_atoi(argv[2]);
	rule->time_to_eat = ft_atoi(argv[3]);
	rule->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rule->count_of_must_eat = ft_atoi(argv[5]);
	else
		rule->count_of_must_eat = INFINITY;
	return (SUCCESS);
}

// int 범위가 제한되어있는지 확인 필요
