#include "philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h> ///+++++++++++++++++++++++++++++++++++++++
#include <stdlib.h>

void	busy_waiting(int time_to_spend)
{
	long long	start_time;
	long long	target_time;

	start_time = get_time();
	target_time = start_time + (long long)time_to_spend * 1000; 

	int	i = 0;
	printf("start : %lld, target : %lld\n", start_time, target_time);
	while (get_time() < target_time)
	{
		usleep(100);
		printf("busy_wating_%d\n", i);
		i++;
	}
}

void	philo_eat(t_rule rule, t_philo *philo, int tid)
{
	printf("%d is eating now\n", tid + 1);
	long long	start_time = get_time();
	busy_waiting(rule.time_to_eat);
	printf("busy_waiting[%d] : %lld\n", tid, start_time - get_time());
	++(philo->eat_count);
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

	philo = (t_philo *)data;
	tid = philo->tid_index;
	while (philo->param->rule->is_dining == TRUE)
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
			usleep(200);
			pthread_mutex_lock(philo->right_fork);
			printf("%d get right fork\n" , tid + 1);
			pthread_mutex_lock(philo->left_fork);
			printf("%d get left fork\n" , tid + 1);
		}
		philo_eat(*(philo->param->rule), philo, philo->tid_index);
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
	if (monitoring_philos(param) == KILL_PROCESS)
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
