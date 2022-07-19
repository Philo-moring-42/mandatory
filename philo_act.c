#include "philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h> ///+++++++++++++++++++++++++++++++++++++++
#include <stdlib.h>

void	philo_eat(t_rule rule, int tid)
{
	printf("%d is eating now\n", tid + 1);
	usleep(rule.time_to_eat);
}

void	philo_sleep(t_rule rule, int tid)
{
	printf("%d is sleeping now\n", tid + 1);
	usleep(rule.time_to_sleep);
}

void	philo_think(int tid)
{
	printf("%d is thinking now\n", tid + 1);
	usleep(200);
}

void	*philo_act(void *data)
{
	int		tid;
	t_philo	*philo;
	int		i;

	philo = (t_philo *)data;
	tid = philo->tid_index;
	i = 0;
	while (i++ < 5)
	{
		if (tid % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			printf("%d get left fork\n" , tid + 1);
			pthread_mutex_lock(philo->right_fork);
			printf("%d get right fork\n" , tid + 1);
		}
		else
		{
			usleep(2000);
			pthread_mutex_lock(philo->right_fork);
			printf("%d get right fork\n" , tid + 1);
			pthread_mutex_lock(philo->left_fork);
			printf("%d get left fork\n" , tid + 1);
		}
		philo_eat(*(philo->param->rule), philo->tid_index);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo_sleep(*(philo->param->rule), philo->tid_index);
		philo_think(philo->tid_index);
			//pthread_create
	}
	return (NULL);
}

int	philo_run(t_rule *rule)
{
	int			i;
	t_param		param;

	if (init_param(&param, rule) == FAIL)
		return (FAIL);
	i = 0;
	while (i < rule->num_of_philo)
	{
		param.philo[i].tid_index = i;
		pthread_create(&param.tids[i], NULL, philo_act, &param.philo[i]);
	//	pthread_join(param.tids[i], NULL);
		++i;
	}
	if (monitoring_philos(param) == SUCCESS)
	{
		i = 0;
		while (i < rule->num_of_philo)
		{
			pthread_detach(param.tids[i]);
			++i;
		}
	}
	return (SUCCESS);
}
