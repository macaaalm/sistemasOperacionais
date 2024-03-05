#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	printf("%d\n",getpid());
	fork();
	printf("%d\n",getpid());
	fork();
	printf("%d\n",getpid());
	fork();
	printf("%d\n",getpid());
	return 0;
}
