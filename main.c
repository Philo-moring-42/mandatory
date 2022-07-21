// /*       rule        */
// 	0. 최대한 놈에 맞춰서 작성한다.
// 	1. 함수는 하나의 역할만 하게 한다.(그 이상 무조건 분리)
// 	2. 명명시 동사가 먼저 나온다 ex> check_argument()
// 	3. 약어는 최대한 사용하지 않는다.(놈 보다 우선)
// 	4. include가 필요한 소스파일에만 헤더 넣기(리링크 방지, 데이터 절약)
                 
#include "philo.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int	is_dining = TRUE;

int	main(int argc, char **argv)
{
	t_rule	rule;

	if (!parsing(argc, argv, &rule))
	{
		printf("FAIL\n");
		return (0);
	}
	if (philo_run(&rule) == FAIL)
		return (0);
		
	// /*             아이디어             */
	// //파싱부                         
	// 	철학자의 수,  굶으면 죽는 시간, 먹는 시간, 자는 시간, (철학자가 최소한 밥을 먹어야 하는 수) -> 구조체 넣는다.
	// 	>> tip. 구조체를 어떻게 할지 많이 이야기 할것.
	// //동작부                           
	// 	초기화(구조체, 초기 값)
	// 	생성(쓰레드)
	// 	선점을 어떻게 할까 (-> 철학자를 최대한 안죽이는 방향으로)
	// 	상호배제 구현 (임계 구간 어떻게 동작 할지)
	// 	출력(어떤 철학자가 포크 잡고, 먹고, 자고, 생각하고 + 죽음) -> 시간이 섞이면 안된다.(시간 순 출력)
	// //체크부	
	// 	죽었는지, 밥 제대로 먹는지 -> 상태를 체크한다. => 어떻게 계속 모니터링을 할까?
	// 	->(메인에서 돌고있는 while (1)내에서 계속 체크한다)
	// 	죽었을 시 프로그램 정상 종료.

}


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
		is_dining = FALSE;
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
		is_dining = FALSE;
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
	while (is_dining == TRUE)
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
		//usleep(10);
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



int	check_eat_count(t_param param)
{
	int	i;
	int	num_of_hogs;

	num_of_hogs = 0;
	i = 0;
	while (i < param.rule->num_of_philo)
	{
		if (param.philo[i].eat_count >= param.rule->count_of_must_eat)
			++num_of_hogs;
		++i;
	}
	if (num_of_hogs == param.rule->num_of_philo)
	{
		param.rule->is_dining = FALSE;
		printf("all philosophers have became hogs\n");
		return (KILL_PROCESS);
	}
	return (KEEP_PROCESS);
}

int	check_death_of_philo(t_param param)
{
	int	i;

	i = 0;
	while (i < param.rule->num_of_philo)
	{
		if (param.philo[i].life == DEAD)
		{
			param.rule->is_dining = FALSE;
			return (KILL_PROCESS);
		}
		++i;
		usleep(100);
	}
	return (KEEP_PROCESS);
}

int	monitoring_philos(t_param param)
{
	while (1)
	{
		if (check_death_of_philo(param) == KILL_PROCESS)
			break;
		if (param.rule->if_count_of_must_eat == TRUE && \
			check_eat_count(param) == KILL_PROCESS)
			break;
	}
	return (KILL_PROCESS);
}


