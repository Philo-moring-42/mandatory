#include "philo.h"

#include <stdio.h>

void	test_print(t_rule rule)
{
	printf("rule.num_of_philo : %d\n", rule.num_of_philo);
	printf("rule.time_to_die : %d\n", rule.time_to_die);
	printf("rule.time_to_eat : %d\n", rule.time_to_eat);
	printf("rule.time_to_sleep : %d\n", rule.time_to_sleep);
	if (rule.if_count_of_must_eat)
		printf("rule.count_of_must_eat : %d\n", rule.count_of_must_eat);
}

static void	get_must_eat(int argc, char **argv, t_rule *rule)
{
	if (argc == 6)
	{
		rule->count_of_must_eat = ft_atoi(argv[5]);
		rule->if_count_of_must_eat = TRUE;
	}
	else
	{
		rule->count_of_must_eat = INFINITY;
		rule->if_count_of_must_eat = FALSE;
	}
}

static int	check_valid_args(t_rule *rule)
{
	if (rule->num_of_philo < 0 || rule->time_to_die < 0
		|| rule->time_to_eat < 0 || rule->time_to_sleep < 0)
		return (FAIL);
	if (rule->if_count_of_must_eat == TRUE && rule->count_of_must_eat < 0)
		return (FAIL);
	return (SUCCESS);
}

int	parsing(int argc, char **argv, t_rule *rule)
{
	if (argc != 5 && argc != 6)
		return (FAIL);
	rule->num_of_philo = ft_atoi(argv[1]);
	rule->time_to_die = ft_atoi(argv[2]);
	rule->time_to_eat = ft_atoi(argv[3]);
	rule->time_to_sleep = ft_atoi(argv[4]);
	get_must_eat(argc, argv, rule);
	if (!check_valid_args(rule))
		return (FAIL);
	test_print(*rule);
	return (SUCCESS);
}

// int 범위가 제한되어있는지 확인 필요
