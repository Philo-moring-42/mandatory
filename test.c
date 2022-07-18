#include <stdio.h>
#include "philo.h"

void	test_print(t_rule rule)
{
	printf("rule.num_of_philo : %d\n", rule.num_of_philo);
	printf("rule.time_to_die : %d\n", rule.time_to_die);
	printf("rule.time_to_eat : %d\n", rule.time_to_eat);
	printf("rule.time_to_sleep : %d\n", rule.time_to_sleep);
	if (rule.if_count_of_must_eat)
		printf("rule.count_of_must_eat : %d\n", rule.count_of_must_eat);
	printf("\n\n\n\n");
}

void	test_philo(t_philo philo, int i)
{
	printf("philo[%d].tid_index : %d\n", i, philo.tid_index);
	printf("philo[%d].life : %d\n", i, philo.life);
	printf("philo[%d].eat_count : %d\n", i, philo.eat_count);
	printf("philo[%d].starving_time : %lld\n", i, philo.starving_time);
	printf("philo[%d].left_fork : %ld\n", i, philo.left_fork->__sig);
	printf("philo[%d].right_fork : %ld\n", i, philo.right_fork->__sig);
	printf("-----------------------------------------\n");
}