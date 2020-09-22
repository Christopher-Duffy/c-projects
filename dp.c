#include <pthread.h>
#include <stdio.h>

#define NUM_DINERS 5

pthread_t threadID[NUM_DINERS];
int x = 10;
void *p = &x;

void *test(){
  printf("this is a test\n");
}

int main(){
  printf("test\n");
  for (int i=0; i<NUM_DINERS; i++){
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    if(pthread_create(&(threadID[i]),&attr,&test,p)!=0){
      printf("There was an error creating a thread");
      return 1;
    }
  }
return 0;
}
