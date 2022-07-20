#include "philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h> ///+++++++++++++++++++++++++++++++++++++++
#include <stdlib.h>

static void	busy_waiting(long long time_to_spend, t_philo *philo, int tid)
{
	long long	start_time;
	long long	target_time;

	start_time = get_time();
	target_time = start_time + time_to_spend; 
	//먹는 동안 죽는지 안죽는지 확인 해야 할까?
	while (get_time() < target_time)
	{
		// printf("%lld / %lld / %d\n", get_time(), start_time, philo->param->rule->time_to_die);
		if (get_time() > start_time + philo->param->rule->time_to_die)
		{
			pthread_mutex_lock(philo->param->dining_or_not);
			philo->param->rule->is_dining = FALSE;
			philo->life = DEAD;
			printf("%d died\n", tid + 1);
			pthread_mutex_unlock(philo->param->dining_or_not);
			return ;
		}
		usleep(1000);
	}
}

static void	philo_eat(t_rule rule, t_philo *philo, int tid)
{
	// pthread_mutex_lock(philo->param->dining_or_not);
	if (rule.is_dining == FALSE)
	{
		// pthread_mutex_unlock(philo->param->dining_or_not);
		return ;
	}
		// pthread_mutex_unlock(philo->param->dining_or_not);
	printf("%d is eating now\n", tid + 1);
	busy_waiting(rule.time_to_eat, philo, tid);
	++(philo->eat_count);
}

static void	philo_sleep(t_rule rule, t_philo *philo, int tid)
{
	// pthread_mutex_lock(philo->param->dining_or_not);
	if (rule.is_dining == FALSE)
	{
		// pthread_mutex_unlock(philo->param->dining_or_not);
		return ;
	}
		// pthread_mutex_unlock(philo->param->dining_or_not);
	printf("%d is sleeping now\n", tid + 1);
	busy_waiting(rule.time_to_sleep, philo, tid);
}

static void	philo_think(t_rule rule, t_philo *philo, int tid)
{
	// pthread_mutex_lock(philo->param->dining_or_not);
	if (rule.is_dining == FALSE)
	{
		return ;
	}
		// pthread_mutex_unlock(philo->param->dining_or_not);
	printf("%d is thinking now\n", tid + 1);
	busy_waiting(200, philo, tid);
}

static void	odd_philo_eat(t_philo *philo, int tid)
{
	pthread_mutex_lock(philo->param->dining_or_not);
	if (philo->param->rule->is_dining == FALSE)
	{
	pthread_mutex_unlock(philo->param->dining_or_not);
		return ;
	}
	pthread_mutex_unlock(philo->param->dining_or_not);
	pthread_mutex_lock(philo->left_fork);
	printf("%d get left fork\n" , tid + 1);
	pthread_mutex_lock(philo->right_fork);
	printf("%d get right fork\n" , tid + 1);
	philo_eat(*(philo->param->rule), philo, philo->tid_index);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	even_philo_eat(t_philo *philo, int tid)
{
	usleep(200);
	pthread_mutex_lock(philo->param->dining_or_not);
	if (philo->param->rule->is_dining == FALSE)
	{
	pthread_mutex_unlock(philo->param->dining_or_not);
		return ;
	}
	pthread_mutex_unlock(philo->param->dining_or_not);
	pthread_mutex_lock(philo->right_fork);
	printf("%d get right fork\n" , tid + 1);
	pthread_mutex_lock(philo->left_fork);
	printf("%d get left fork\n" , tid + 1);
	philo_eat(*(philo->param->rule), philo, philo->tid_index);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_act(void *data)
{
	int		tid;
	t_philo	*philo;

	philo = (t_philo *)data;
	tid = philo->tid_index;
	// pthread_mutex_lock(philo->param->dining_or_not);
	while (philo->param->rule->is_dining == TRUE)
	{
		// pthread_mutex_unlock(philo->param->dining_or_not);
		if (tid % 2 == 0)
			odd_philo_eat(philo, tid);
		else
			even_philo_eat(philo, tid);
		philo_sleep(*(philo->param->rule), philo, philo->tid_index);
		philo_think(*(philo->param->rule), philo, philo->tid_index);
		// pthread_mutex_lock(philo->param->dining_or_not);
	}
	// pthread_mutex_unlock(philo->param->dining_or_not);
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
