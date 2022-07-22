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
		usleep(100);
}

static void	philo_eat(t_rule *rule, t_philo *philo, int tid)
{
	if (rule->is_dining == FALSE)
		return ;
    pthread_mutex_lock(&philo->param->print_lock);
	print_terminal(philo->param, tid + 1, "is eating");
	busy_waiting(rule->time_to_eat, philo, tid);
	++(philo->eat_count);
}

static void	philo_sleep(t_rule *rule, t_philo *philo, int tid)
{
	if (rule->is_dining == FALSE)
		return ;
    pthread_mutex_lock(&philo->param->print_lock);
	print_terminal(philo->param, tid + 1, "is sleeping");
	busy_waiting(rule->time_to_sleep, philo, tid);
}

static void	philo_think(t_rule *rule, t_philo *philo, int tid)
{
	if (rule->is_dining == FALSE)
		return ;
    pthread_mutex_lock(&philo->param->print_lock);
	print_terminal(philo->param, tid + 1, "is thinking");
	usleep(50);
}

static void	odd_philo_eat(t_philo *philo, int tid)
{
	long long	start_time;

	start_time = get_time();
	pthread_mutex_lock(philo->left_fork);
	print_terminal(philo->param, tid + 1, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_terminal(philo->param, tid + 1, "has taken a fork");
	philo_eat(philo->param->rule, philo, philo->tid_index);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	even_philo_eat(t_philo *philo, int tid)
{
	long long	start_time;

	usleep(50);
	start_time = get_time();
	pthread_mutex_lock(philo->right_fork);
	print_terminal(philo->param, tid + 1, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_terminal(philo->param, tid + 1, "has taken a fork");
	philo_eat(philo->param->rule, philo, philo->tid_index);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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
			odd_philo_eat(philo, tid);
		else
			even_philo_eat(philo, tid);
		philo->start_starving_time = get_time();
		philo_sleep(philo->param->rule, philo, philo->tid_index);
		philo_think(philo->param->rule, philo, philo->tid_index);
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
		if (i == 0)
			param.start_time = get_time();
		pthread_create(&param.tids[i], NULL, philo_act, &param.philo[i]);
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
