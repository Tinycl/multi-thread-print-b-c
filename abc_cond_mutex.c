#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


static pthread_cond_t cond1;// = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond2;// = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond3;// = PTHREAD_COND_INITIALIZER;

int count = 0;
void *threadfun1(void* arg)
{
    int a = 10; //a--
    while(a--)
    {
        //printf("aa\n");
     
        pthread_mutex_lock(&mtx);
        while(count != 1)
            pthread_cond_wait(&cond1,&mtx);
        printf("threadfun1: A\n");
        count = 2;
        pthread_mutex_unlock(&mtx);
        pthread_cond_signal(&cond2);

     
    }   
}
void *threadfun2(void* arg)
{
    int a = 10; //a--
    while(a--)
    {   
        //printf("bb\n");
       
        pthread_mutex_lock(&mtx);
        while(count != 2)
            pthread_cond_wait(&cond2,&mtx);
        printf("threadfun2: B\n");
        count = 3;
        pthread_mutex_unlock(&mtx);
        pthread_cond_signal(&cond3);

    }
}
void *threadfun3(void* arg)
{
    int a = 10; //a--
    while(a--)
    {   
       // printf("cc\n");

        pthread_mutex_lock(&mtx);
        while(count != 3)
            pthread_cond_wait(&cond3,&mtx);
        printf("threadfun3: C\n");
        count =1 ;
        pthread_mutex_unlock(&mtx);
        pthread_cond_signal(&cond1);        
    }
}

int main()
{
    int i = 0;
    int ret[3];
    pthread_t pid[3];
    pthread_cond_init(&cond1,NULL);
    pthread_cond_init(&cond2,NULL);
    pthread_cond_init(&cond3,NULL);
    pthread_create(&pid[0],NULL, threadfun1,NULL);
    pthread_create(&pid[1],NULL, threadfun2,NULL);
    pthread_create(&pid[2],NULL, threadfun3,NULL);
    count = 1;
    sleep(2);
    pthread_cond_signal(&cond1);

    for(i = 0; i < 3; i++)
    {
       ret[i] = pthread_join(pid[i],NULL);
       if(ret[i] != 0)
       {
			exit(-1);
       }
    }
    
    printf("main thread is over\n");
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond1); 
    pthread_cond_destroy(&cond2);
    pthread_cond_destroy(&cond3);
    return 0;
}

 /*
        if(pthread_mutex_trylock(&mtx) != 0)
        {
            pthread_mutex_unlock(&mtx);
        }
*/