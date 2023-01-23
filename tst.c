#include<stdio.h>
#include<unistd.h>
#include<pthread.h>



void *nothing(void *p)
{
	printf("hello from the thread [%lu]\n", (unsigned long)p);
	sleep(2);
	printf("BYE\n");
	return NULL;
}
int main()
{
	pthread_t t1;
	pthread_t t2;
	pthread_create(&t1, NULL, nothing, &t1);
	pthread_join(t1, NULL);
	pthread_create(&t2, NULL, nothing, &t2); 
	pthread_join(t2, NULL);
}