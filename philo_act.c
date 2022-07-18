#include "philo.h"
#include <pthread.h>
#include <stdio.h> ///+++++++++++++++++++++++++++++++++++++++

void	*philo_act(){	}


void	philo_run(t_rule *rule)
{
	int			i;
	pthread_t	tids[rule->num_of_philo];
	
	i = 0;
	while (i < rule->num_of_philo)
	{
		pthread_create(&tids[i], NULL, philo_act, NULL);
	}
}

