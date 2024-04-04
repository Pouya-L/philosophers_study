#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_thread_data
{
	int				*i;
	pthread_mutex_t	*mutex;
}					t_thread_data;


void* routine(void *args)
{
	int j = 0;
	t_thread_data *data = (t_thread_data*)args;
	while (j < 1000000)
	{
		pthread_mutex_lock(data->mutex);
		(*(data->i))++;
		j++;
		pthread_mutex_unlock(data->mutex);
	}
}

int	main(void)
{
	int	i;
	pthread_t t1, t2;
	pthread_mutex_t mutex;
	t_thread_data data;

	i = 0;
	data.i = &i;
	data.mutex = &mutex;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, &data) != 0)
		return 1;
	if (pthread_create(&t2, NULL, &routine, &data) != 0)
		return 2;
	if (pthread_join(t1, NULL) != 0)
		return 11;
	if (pthread_join(t2, NULL) != 0)
		return 21;
	printf("i = %d\n", i);
	pthread_mutex_destroy(&mutex);
	return (0);

}
