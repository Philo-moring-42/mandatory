#include "philo.h"
#include <stdio.h>

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i] || i == n - 1)
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void    print_terminal(t_param *param, int tid, char *str)
{
    // pthread_mutex_lock(&param->print_lock);
    printf("[%lld] %d %s\n", get_time() - param->start_time, tid, str);
    if (!ft_strncmp(str, "died", 5))
        return ;
    pthread_mutex_unlock(&param->print_lock);
}
