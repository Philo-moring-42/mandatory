#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define SUCCESS	1
# define FAIL		0

# define INFINITY	-1
# define TRUE		1
# define FALSE		0

typedef struct s_rule
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	count_of_must_eat;
	int	if_count_of_must_eat;
}	t_rule;

typedef struct s_param
{
	t_rule			*rule;
	pthread_mutex_t	*forks;
	pthread_t		*tids;
}	t_param;

/* ft_atoi.c */
int	ft_is_digit(int c);
int	ft_atoi(const char *str);

/* parsing.c */
int	parsing(int argc, char **argv, t_rule *rule);

/* philo_act */
int	philo_run(t_rule *rule);


#endif
