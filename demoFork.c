/* Kashif Lodhi CPSC 6125
   09/09/2020   */



#include  <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <string.h>

#define   MAX_COUNT  5

void  ChildProcess(void);                /* ChildProcess   */
void  ParentProcess(void);               /* ParentProcess  */
void* createSharedMemory(size_t size);

int main(void)
{
     char myString[50];
     pid_t  pid;
     int arr[10];
     
     strcpy(myString, "This is my original string");
     void *sharedMem = createSharedMemory(sizeof(myString));
     memcpy(sharedMem, myString, sizeof(myString));
     printf("%s\n",myString);
     pid = fork();
     if (pid == 0){
     	  ChildProcess();
          strcpy(sharedMem, "The child process has editted the string!");
     }
     else{
          wait(NULL);
          ParentProcess();
          strcpy(myString,sharedMem);
          printf("%s\n",myString);
     }
     return 0;
}

void* createSharedMemory(size_t size){
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANONYMOUS;
  return mmap(NULL, size, protection, visibility,-1,0);
}

void  ChildProcess(void)
{
     int   i;
     pid_t pid_C = getpid();
     printf("Childprocess ID = %d\n", pid_C);
     for (i = 1; i <= MAX_COUNT; i++)
          printf("This line is from child, value = %d\n", i);
     printf("*** Child process is done ***\n\n");
}

void  ParentProcess(void)
{
     int   i;
     pid_t pid_P = getpid();
	 printf("ParentProcess ID = %d\n", pid_P);
     for (i = 1; i <= MAX_COUNT; i++)
          printf("This line is from parent, value = %d\n", i);
     printf("*** Parent is done ***\n");
}
