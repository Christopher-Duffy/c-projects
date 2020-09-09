/* Kashif Lodhi CPSC 6125
   09/09/2020   */



#include  <stdio.h>
#include  <sys/types.h>

#define   MAX_COUNT  2400

void  ChildProcess(void);                /* ChildProcess   */
void  ParentProcess(void);               /* ParentProcess  */

void  main(void)
{
     pid_t  pid;

     pid = fork();
     if (pid == 0) 
          ChildProcess();
     else 
          ParentProcess();
}

void  ChildProcess(void)
{
     int   i;
	 pid_t pid_C = getpid();
     printf("Childprocess ID = %d\n", pid_C);
     for (i = 1; i <= MAX_COUNT; i++)
          printf("   This line is from child, value = %d\n", i);
     printf("   *** Child process is done ***\n");
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