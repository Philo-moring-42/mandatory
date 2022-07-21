#include "philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h> ///+++++++++++++++++++++++++++++++++++++++
#include <stdlib.h>

static void	busy_waiting(long long time_to_spend, t_philo *philo, int tid)
{
	long long	target_time;

	target_time = get_time() + time_to_spend; 
	while (get_time() < target_time)
	{
		//if (get_time() > start_time + philo->param->rule->time_to_die)
		if (philo->starving_time >= philo->param->rule->time_to_die)
		{
			philo->param->rule->is_dining = FALSE;
			philo->life = DEAD;
			printf("[%lld] %d died\n", get_time() - *philo->param->start_time, tid + 1);
			return ;
		}
		usleep(100);
		philo->starving_time += 0.1;
	}
}

static void	philo_eat(t_rule rule, t_philo *philo, int tid)
{
	if (rule.is_dining == FALSE)
		return ;
	printf("[%lld] %d is eating\n", get_time() - *philo->param->start_time, tid + 1);
	busy_waiting(rule.time_to_eat, philo, tid);
	++(philo->eat_count);
	philo->starving_time = 0;
}

static void	philo_sleep(t_rule rule, t_philo *philo, int tid)
{
	if (rule.is_dining == FALSE)
		return ;
	printf("[%lld] %d is sleeping\n", get_time() - *philo->param->start_time, tid + 1);
	busy_waiting(rule.time_to_sleep, philo, tid);
}

static void	philo_think(t_rule rule, t_philo *philo, int tid)
{
	if (rule.is_dining == FALSE)
		return ;
	printf("[%lld] %d is thinking\n", get_time() - *philo->param->start_time, tid + 1);
	//busy_waiting(200, philo, tid);
}

static void	odd_philo_eat(t_philo *philo, int tid)
{
	long long	start_time;

	start_time = get_time();
	pthread_mutex_lock(philo->left_fork);
	philo->starving_time += get_time() - start_time; 
	if (philo->starving_time >= philo->param->rule->time_to_die)
	{
		philo->param->rule->is_dining = FALSE;
		philo->life = DEAD;
		printf("[%lld] %d died\n", get_time() - *philo->param->start_time, tid + 1);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	printf("[%lld] %d has taken a fork\n", get_time() - *philo->param->start_time, tid + 1);
	pthread_mutex_lock(philo->right_fork);
	printf("[%lld] %d has taken a fork\n", get_time() - *philo->param->start_time, tid + 1);
	philo_eat(*(philo->param->rule), philo, philo->tid_index);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	even_philo_eat(t_philo *philo, int tid)
{
	long long	start_time;

	// usleep(200);
	// philo->starving_time += 0.2;
	start_time = get_time();
	pthread_mutex_lock(philo->right_fork);
	philo->starving_time += get_time() - start_time; 
	if (philo->starving_time >= philo->param->rule->time_to_die)
	{
		philo->param->rule->is_dining = FALSE;
		philo->life = DEAD;
		printf("[%lld] %d died\n", get_time() - *philo->param->start_time, tid + 1);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	printf("[%lld] %d has taken a fork\n", get_time() - *philo->param->start_time, tid + 1);
	pthread_mutex_lock(philo->left_fork);
	printf("[%lld] %d has taken a fork\n", get_time() - *philo->param->start_time, tid + 1);
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
	*philo->param->start_time = get_time();
	while (philo->param->rule->is_dining == TRUE)
	{
		if (tid % 2 == 0)
			odd_philo_eat(philo, tid);
		else
			even_philo_eat(philo, tid);
		philo_sleep(*(philo->param->rule), philo, philo->tid_index);
		philo_think(*(philo->param->rule), philo, philo->tid_index);
	}
	return (NULL);
}

int	philo_run(t_rule *rule, t_param *param)
{
	int			i;

	i = 0;
	while (i < rule->num_of_philo)
	{
		param->philo[i].tid_index = i;
		pthread_create(&param->tids[i], NULL, philo_act, &param->philo[i]);
		usleep(10);
		++i;
	}
	if (monitoring_philos(*param) == KILL_PROCESS)
	{
		i = 0;
		while (i < rule->num_of_philo)
		{
			pthread_join(param->tids[i], NULL);
			++i;
		}
	}
	return (SUCCESS); //반환할 일이 없음.
}
