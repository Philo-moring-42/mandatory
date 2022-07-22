/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeong <hjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:35:04 by hjeong            #+#    #+#             */
/*   Updated: 2022/07/22 17:05:44 by hjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define SUCCESS	1
# define FAIL		0

# define INFINITY	-999
# define TRUE		1
# define FALSE		0

# define KILL_PROCESS	1
# define KEEP_PROCESS	0

typedef struct s_philo	t_philo;

typedef struct s_rule
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	count_of_must_eat;
	int	if_count_of_must_eat;
	int	is_dining;
}	t_rule;

typedef struct s_param
{
	long long		start_time;
	struct s_rule	*rule;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	is_dining_lock;
	pthread_mutex_t	get_time_lock;
	pthread_t		*tids;
	t_philo			*philo;
}	t_param;

typedef struct s_philo
{
	struct s_param	*param;
	int				tid_index;
	int				eat_count;
	long long		start_starving_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

/* ft_atoi.c */
int			ft_is_digit(int c);
int			ft_atoi(const char *str);

/* get_time.c */
long long	get_time(t_param *param);

/* init_func.c */
int			init_param(t_param *param, t_rule *rule);

/* monitoring.c */
int			monitoring_philos(t_param *param);

/* parsing.c */
int			parsing(int argc, char **argv, t_rule *rule);

/* philo_act.c */
int			philo_run(t_rule *rule);

/* philo_act2.c */
void		spending_time(t_param *param, long long time_to_spend);
void		philo_eat(t_rule *rule, t_philo *philo, int tid);
void		philo_sleep(t_rule *rule, t_philo *philo, int tid);
void		philo_think(t_rule *rule, t_philo *philo, int tid);

/* print.c */
void		print_terminal(t_param *param, int tid, char *str);

#endif
