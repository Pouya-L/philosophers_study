#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void	*roll_dice()
{
	int	val;
	int	*res;

	val = (rand() % 6) + 1;
	res = malloc(sizeof(int));
	*res = val;
	printf("in thread val : %d\n", val);
	return (void *)res;
}

int	main(void)
{
	int	*res;
	srand(time(NULL));
	pthread_t th;
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return 1;
	if (pthread_join(th, (void **)&res) != 0)
		return 2;
	printf("your dice roll: %d\n", *res);
	free(res);
	return (0);
}
