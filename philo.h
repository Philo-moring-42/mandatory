#ifndef PHILO_H
# define PHILO_H

# define SUCCESS	1
# define FAIL		0
# define INFINITY	-1

typedef struct s_rule
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	count_of_must_eat;
}	t_rule;

int	ft_atoi(const char *str);

#endif
