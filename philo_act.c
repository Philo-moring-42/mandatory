#include "philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h> ///+++++++++++++++++++++++++++++++++++++++
#include <stdlib.h>

void	busy_waiting(long long time_to_spend)
{
	long long	start_time;
	long long	target_time;

	start_time = get_time();
	target_time = start_time + time_to_spend; 
	//먹는 동안 죽는지 안죽는지 확인 해야 할까?
	// if (get_time > start_time + time_to_die -->is dinig == false)
	// 	return ;
	while (get_time() < target_time)
		usleep(100);
}

void	philo_eat(t_rule rule, t_philo *philo, int tid)
{
	// if (rule.is_dining == FALSE)
	// 	return
	printf("%d is eating now\n", tid + 1);
	busy_waiting(rule.time_to_eat);
	++(philo->eat_count);
}

void	philo_sleep(t_rule rule, int tid)
{
	// if (rule.is_dining == FALSE)
	// 	return
	printf("%d is sleeping now\n", tid + 1);
	busy_waiting(rule.time_to_sleep);
	usleep(rule.time_to_sleep);
}

void	philo_think(int tid)
{
	// if (rule.is_dining == FALSE)
	// 	return
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
			pthread_join(param.tids[i], NULL);
			++i;
		}
	}
	return (SUCCESS); //반환할 일이 없음.
}
