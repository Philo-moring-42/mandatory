#ifndef PHILO_H
# define PHILO_H

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

/* ft_atoi.c */
int	ft_atoi(const char *str);

/* parsing.c */
int	parsing(int argc, char **argv, t_rule *rule);

#endif
