#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

sem_t sem1,sem2,sem3;


void *threadfun1(void* arg)
{
    int a = 10; //a--
    while(1)
    {
        sem_wait(&sem1);
        printf("threadfun1: A\n");
        sem_post(&sem2);
     }
}
void *threadfun2(void* arg)
{
    int a = 10; //a--
    while(1)
    {   
        sem_wait(&sem2);
        printf("threadfun2: B\n");
        sem_post(&sem3);
    }
}
void *threadfun3(void* arg)
{
    int a = 10; //a--
    while(1)
    {   
        sem_wait(&sem3);
        printf("threadfun3: C\n");
        sem_post(&sem1);
           
    }
}

int main()
{
    int i = 0;
    int ret[3];
    pthread_t pid[3];
    sem_init(&sem1,0,0);
    sem_init(&sem2,0,0);
    sem_init(&sem3,0,0);
    pthread_create(&pid[0],NULL, threadfun1,NULL);
    pthread_create(&pid[1],NULL, threadfun2,NULL);
    pthread_create(&pid[2],NULL, threadfun3,NULL);
    
    sleep(2);
    sem_post(&sem1);
    for(i = 0; i < 3; i++)
    {
       ret[i] = pthread_join(pid[i],NULL);
       if(ret[i] != 0)
       {
			exit(-1);
       }
    }
    
    printf("main thread is over\n");
      
    return 0;
}
