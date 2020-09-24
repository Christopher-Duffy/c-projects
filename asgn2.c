#include <stdio.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10
#define MAX 100

//fills an array with 0s
void fillArray(int* ptr,int size);
//adds a random number to a random array cell
void incrementRandom(int* ptr, int size);
//checks an array for any values > MAX and sets the cell to 0
void checkValues(int* ptr, int size);
//makes shared memory with mmap
void* createSharedMemory(size_t size);

//for testing
void printArray(int* ptr,int size);

int main(void){
  //seed random
  srand(time(0));
  //make and fill array
  int arr[SIZE];
  fillArray(arr,SIZE);
  //make and init binary semaphores for shared space
  sem_t lock1;
  sem_t lock2;
  sem_init(&lock1,1,1);
  sem_init(&lock2,1,1);
  //create shared memory for arr, lock1, lock 2
  void *sharedArr = createSharedMemory(sizeof(arr));
  memcpy(sharedArr, arr, sizeof(arr));
  void *slock1 = createSharedMemory(sizeof(lock1));
  memcpy(slock1, &lock1, sizeof(lock1));
  void *slock2 = createSharedMemory(sizeof(lock2));
  memcpy(slock2, &lock2, sizeof(lock2));
  //cast shared locks as sem_t*
  sem_t* sharedLock1 = slock1;
  sem_t* sharedLock2 = slock2;
  //fork
  int threadID = fork();
  if(threadID!=0){
    //parent only process
    while(1){
      sleep(0);
      if(sem_trywait(sharedLock1) == 0 && sem_trywait(sharedLock2)==0){  
      	incrementRandom(sharedArr,SIZE);
      	sem_post(sharedLock1);
      	sem_post(sharedLock2);
      }
    }
  }else{
    
      //child only process
    while(1){
      sleep(0);
      if(sem_trywait(sharedLock1) == 0  && sem_trywait(sharedLock2)==0){
        printArray(sharedArr,SIZE);
        checkValues(sharedArr,SIZE);
        sem_post(sharedLock1);
        sem_post(sharedLock2);
      }
    }
  }
  //this stuff will never actually occur, but it's good practice
  //release the shared memory
  munmap(sharedArr,sizeof(arr));
  munmap(slock1,sizeof(lock1));
  munmap(slock2,sizeof(lock2));
  //destoy the semaphores
  sem_destroy(&lock1);
  sem_destroy(&lock2);
  return 0;
}

void fillArray(int* ptr,int size){
  int* first = ptr;
  for(ptr;ptr<first+size; ptr++){
    *ptr=0;
  }
}

void incrementRandom(int* ptr, int size){
  ptr = ptr + rand()%size;
  *ptr = *ptr + rand()%MAX;
}

void checkValues(int* ptr, int size){
  int* first = ptr;
  for(ptr;ptr<first+size; ptr++){
    if(*ptr>MAX){
      int index = ptr-first;
      printf("Cell %d exceeds %d, 'process exceeds limit on system calls'\n",index,MAX);
      *ptr = 0;
    }
  }
}

void* createSharedMemory(size_t size){
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANONYMOUS;
  return mmap(NULL, size, protection, visibility,-1,0);
}

void printArray(int* ptr,int size){
  int* first = ptr;
  for(ptr;ptr<first+size; ptr++){
    printf("%d ",*ptr);
  }
  printf("\n");
}
