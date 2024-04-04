#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void 	*routine(void *arg)
{
	int	i;

	i = *(int *)arg;
	printf("%d, ", primes[i]);
	free(arg);
}

int	main(void)
{
	int	i;
	int *a;
	pthread_t th[10];

	i = 0;
	while (i < 10)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			perror("failed to create thread\n");
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread\n");
		i++;
	}

}
