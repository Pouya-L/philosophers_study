#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_thread_data
{
	int				*i;
	pthread_mutex_t	*mutex;
	// pthread_t		*threads;
}					t_thread_data;

void	*routine(void *args)
{
	t_thread_data *data;

	data = (t_thread_data *)args;
	int	j;

	j = 0;
	while (j < 1000000)
	{
		pthread_mutex_lock(data->mutex);
		(*(data->i))++;
		j++;
		pthread_mutex_unlock(data->mutex);
	}
	return (NULL);
}

int	main(void)
{
	int	i;
	pthread_t threads[4];
	int j;
	t_thread_data data;
	pthread_mutex_t mutex;

	i = 0;
	j = 0;
	data.i = &i;
	data.mutex = &mutex;

	data.i = &i;
	pthread_mutex_init(data.mutex, NULL);
	while (j < 4)
	{
		if (pthread_create(&threads[j], NULL, &routine, &data) != 0)
		{
			perror("Failed to create threads\n");
			return (1);
		}
		printf("thread %d has started\n", j);
		j++;
	}
	j = 0;
	while (j < 4)
	{
		if (pthread_join(threads[j], NULL) != 0)
		{
			perror("Thread couldn't be joined\n");
			return (2);
		}
		printf("thread %d has finished execution\n", j);
		j++;
	}
	pthread_mutex_destroy(&mutex);
	printf("i is %d\n", i);
}
