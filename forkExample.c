#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <string.h>

#define SIZE 10

void swap (int *xp, int *yp){
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void selectionSort(int *ptr, int size){
  int *minimum, *i, *j;
  int numSwaps = 0;
  bool swapped;
 
  for(i = ptr;i<size+ptr-1;i++){
    minimum = i;
    swapped = false;
    for(j=i+1;j<size+ptr;j++){
    	if(*j<*minimum){
    	  minimum = j;
    	  swapped = true;
    	}
    }
    swap(minimum,i);
    if (swapped){
      numSwaps++;
    }
  }
  if (numSwaps == 0){
    printf("The array was already sorted!\n");
  } else{
    printf("Array sorted with %d swaps! \n", numSwaps);
  }
   
}

void printArray(int *ptr, int size){
  int *first = ptr;
  for(ptr;ptr<first+size; ptr++){
    printf("%d ", *ptr);
  }
  printf("\n");
}

void fillArray(int *ptr, int size){
  int *first = ptr;
  srand(time(0));
  for(ptr;ptr<first+size; ptr++){
    *ptr = rand()%10;
  }
}

void* createSharedMemory(size_t size){
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANONYMOUS;
  return mmap(NULL, size, protection, visibility,-1,0);
}

int main(void){
  int arr[SIZE];
  fillArray(arr,SIZE);
  
  void *sharedMemory = createSharedMemory(sizeof(arr));
  memcpy(sharedMemory, arr, sizeof(arr));
  
  int parent = fork();
  if(parent!=0){
    wait(NULL);
    printf("I am the parent thread\n");
  } else{
    printf("I am the child thread\n");
  }
  printArray(sharedMemory,SIZE);
  selectionSort(sharedMemory,SIZE);
  printArray(sharedMemory,SIZE);
  return 0;
}
